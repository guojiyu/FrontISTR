!======================================================================!
!                                                                      !
!   Software Name : HEC-MW Library for PC-cluster                      !
!         Version : 2.3                                                !
!                                                                      !
!     Last Update : 2006/06/01                                         !
!        Category : Linear Solver                                      !
!                                                                      !
!            Written by Kengo Nakajima (Univ. of Tokyo)                !
!                                                                      !
!     Contact address :  IIS,The University of Tokyo RSS21 project     !
!                                                                      !
!     "Structural Analysis System for General-purpose Coupling         !
!      Simulations Using High End Computing Middleware (HEC-MW)"       !
!                                                                      !
!======================================================================!

!C
!C*** 
!C*** module hecmw_solver_SR_mm
!C***
!C
      module hecmw_solver_SR_mm
      contains
!C
!C*** SOLVER_SEND_RECV
!C
      subroutine  HECMW_SOLVE_SEND_RECV_mm                              &
     &                ( N, m, NEIBPETOT, NEIBPE,                        &
     &                  STACK_IMPORT, NOD_IMPORT,                       &
     &                  STACK_EXPORT, NOD_EXPORT, WS, WR, X,            &
     &                  SOLVER_COMM,my_rank)

      use hecmw_util
      implicit REAL*8 (A-H,O-Z)
!      include  'mpif.h'
!      include  'hecmw_config_f.h'

      integer(kind=kint )                , intent(in)   ::  N, m
      integer(kind=kint )                , intent(in)   ::  NEIBPETOT
      integer(kind=kint ), pointer :: NEIBPE      (:)
      integer(kind=kint ), pointer :: STACK_IMPORT(:)
      integer(kind=kint ), pointer :: NOD_IMPORT  (:)
      integer(kind=kint ), pointer :: STACK_EXPORT(:)
      integer(kind=kint ), pointer :: NOD_EXPORT  (:)
      real   (kind=kreal), dimension(m*N), intent(inout):: WS
      real   (kind=kreal), dimension(m*N), intent(inout):: WR
      real   (kind=kreal), dimension(m*N), intent(inout):: X
      integer(kind=kint )                , intent(in)   ::SOLVER_COMM
      integer(kind=kint )                , intent(in)   :: my_rank

      integer(kind=kint ), dimension(:,:), allocatable :: sta1
      integer(kind=kint ), dimension(:,:), allocatable :: sta2
      integer(kind=kint ), dimension(:  ), allocatable :: req1
      integer(kind=kint ), dimension(:  ), allocatable :: req2  

      integer(kind=kint ), save :: NFLAG
      data NFLAG/0/
      ! local valiables
      integer(kind=kint ) :: neib,istart,inum,k,ii,ierr
!C
!C-- INIT.
      allocate (sta1(MPI_STATUS_SIZE,NEIBPETOT))
      allocate (sta2(MPI_STATUS_SIZE,NEIBPETOT))
      allocate (req1(NEIBPETOT))
      allocate (req2(NEIBPETOT))
       
!C
!C-- SEND
      do neib= 1, NEIBPETOT
        istart= STACK_EXPORT(neib-1)
        inum  = STACK_EXPORT(neib  ) - istart
!$omp parallel do private (ii)
!*voption indep (WS,X,NOD_EXPORT)
!VOPTION INDEP, VEC
!CDIR NODEP
        do k= istart+1, istart+inum
          ii   = m*NOD_EXPORT(k)
          do kk= 1, m
            WS(m*k-kk+1)= X(ii-kk+1)
          enddo
        enddo
!$omp end parallel do

        call MPI_ISEND (WS(m*istart+1), m*inum,MPI_DOUBLE_PRECISION,    &
     &                  NEIBPE(neib), 0, SOLVER_COMM, req1(neib), ierr)
      enddo

!C
!C-- RECEIVE
      do neib= 1, NEIBPETOT
        istart= STACK_IMPORT(neib-1)
        inum  = STACK_IMPORT(neib  ) - istart
        call MPI_IRECV (WR(m*istart+1), m*inum, MPI_DOUBLE_PRECISION,   &
     &                  NEIBPE(neib), 0, SOLVER_COMM, req2(neib), ierr)
      enddo

      call MPI_WAITALL (NEIBPETOT, req2, sta2, ierr)
   
      do neib= 1, NEIBPETOT
        istart= STACK_IMPORT(neib-1)
        inum  = STACK_IMPORT(neib  ) - istart
!$omp parallel do private (ii)
!*voption indep (WR,X,NOD_IMPORT)
!VOPTION INDEP, VEC
!CDIR NODEP
      do k= istart+1, istart+inum
        ii   = m*NOD_IMPORT(k)
        do kk= 1, m
          X(ii-kk+1)= WR(m*k-kk+1)
        enddo
      enddo
!$omp end parallel do
      enddo

      call MPI_WAITALL (NEIBPETOT, req1, sta1, ierr)

      deallocate (sta1, sta2, req1, req2)

      end subroutine hecmw_solve_send_recv_mm
      end module     hecmw_solver_SR_mm



