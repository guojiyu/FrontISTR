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

!C*** 
!C*** module hecmw_solver_GMRES_33
!C***
!
      module hecmw_solver_GMRES_33
      contains
!C
!C*** hecmw_solve_GMRES_33
!C
      subroutine hecmw_solve_GMRES_33                                   &
     &   (N, NP, NPL, NPU, D, AL, INL, IAL, AU, INU, IAU,               &
     &    B, X, ALU, RESID, ITER, ERROR, my_rank,                       &
     &    NEIBPETOT, NEIBPE, STACK_IMPORT, NOD_IMPORT,                  &
     &                       STACK_EXPORT, NOD_EXPORT,                  &
     &                       SOLVER_COMM , PRECOND, iterPREmax, NREST,  &
     &    Tset, Tsol, Tcomm, ITERlog)     

      use hecmw_util
      use m_hecmw_solve_error
      use m_hecmw_comm_f
      use hecmw_solver_SR_33

      implicit none

      integer(kind=kint ), intent(in):: N, NP, NPU, NPL, my_rank
      integer(kind=kint ), intent(in):: NEIBPETOT
      integer(kind=kint ), intent(in):: SOLVER_COMM
      integer(kind=kint ), intent(in):: PRECOND, ITERlog

      integer(kind=kint ), intent(inout):: ITER, ERROR
      real   (kind=kreal), intent(inout):: RESID, Tset, Tsol, Tcomm

      real(kind=kreal), dimension(3*NP) , intent(inout):: B, X
      real(kind=kreal), dimension(9*NPL), intent(inout):: AL
      real(kind=kreal), dimension(9*NPU), intent(inout):: AU
      real(kind=kreal), dimension(9*N  ), intent(inout):: ALU
      real(kind=kreal), dimension(9*NP ), intent(inout):: D

      integer(kind=kint ), dimension(0:NP) ,intent(in) :: INU, INL
      integer(kind=kint ), dimension(  NPL),intent(in) :: IAL
      integer(kind=kint ), dimension(  NPU),intent(in) :: IAU

      integer(kind=kint ), pointer :: NEIBPE(:)
      integer(kind=kint ), pointer :: STACK_IMPORT(:), NOD_IMPORT(:)
      integer(kind=kint ), pointer :: STACK_EXPORT(:), NOD_EXPORT(:)

      real(kind=kreal), dimension(:),    allocatable :: WS, WR
      real(kind=kreal), dimension(:,:),  allocatable :: WW

      integer(kind=kint ) :: MAXIT, iterPREmax, NREST

      real   (kind=kreal) :: TOL

      real   (kind=kreal), dimension(:),   allocatable :: SS
      real   (kind=kreal), dimension(:,:), allocatable :: H

      integer(kind=kint ) :: AV, CS, SN, R, S, V, W, Y, ZP, ZQ

      real   (kind=kreal)   ZERO, ONE
      parameter ( ZERO = 0.0D+0, ONE = 1.0D+0 )
 
      integer(kind=kint ) :: NRK,i,k,kk,j,jj,jSR,jSB,INFO,ik,iSR,isL,ieL,isU,ieU,kSB
      integer(kind=kint ) :: indexA,indexB,indexC,kSR,IROW,iterPRE
      real   (kind=kreal) :: S_TIME,E_TIME,S1_TIME,E1_TIME
      real   (kind=kreal) :: LDH,LDW,BNRM20,BNRM2,DNRM2,DNRM20,RNORM
      real   (kind=kreal) :: COMMtime,COMPtime, coef,VAL0,VAL,VCS,VSN,DTEMP,AA,BB,R0,SCALE,RR
      real   (kind=kreal) :: X1,X2,X3,WVAL1,WVAL2,WVAL3,SW1,SW2,SW3

      S_TIME= HECMW_WTIME()
!C
!C-- INIT.
      ERROR= 0
      NRK= NREST + 7

      allocate (H (NRK,NRK))
      allocate (WW(3*NP,NRK))
      allocate (WS(3*NP))
      allocate (WR(3*NP))
      allocate (SS(NRK))

      COMMtime= 0.d0
      COMPtime= 0.d0

      LDH= NREST + 2
      LDW= N

      MAXIT = ITER
      TOL   = RESID

      R  = 1
      ZP = R + 1
      ZQ = R + 2
      S  = R + 3
      W  = S + 1
      Y  = W
      AV = Y  + 1
      V  = AV + 1

!C
!C-- Store the Givens parameters in matrix H.
      CS= NREST + 1
      SN= CS    + 1

!C
!C
!C +--------------------+
!C | {r}= {b} - [A]{x0} |
!C +--------------------+
!C===
      indexB= R
      call hecmw_solve_init_resid_33 (indexB)
!C===

      BNRM20= 0.d0
      do ik= 1, N
        iSR= 3*ik-2
        BNRM20= BNRM20 + B(iSR  )**2 + B(iSR+1)**2 + B(iSR+2)**2 
      enddo

      call HECMW_allREDUCE_DP1 (BNRM20, BNRM2, HECMW_SUM, SOLVER_COMM )
!C      call MPI_allREDUCE (BNRM20, BNRM2, 1, MPI_DOUBLE_PRECISION,       &
!C     &                    MPI_SUM, SOLVER_COMM, ierr)

      if (BNRM2.eq.ZERO) BNRM2= ONE

      E_TIME= HECMW_WTIME()
      Tset= Tset + E_TIME - S_TIME
!C===
      
      S1_TIME= HECMW_WTIME()
      ITER= 0
   10 continue

!C
!C************************************************ GMRES Iteration
!C
        I= 0
!C
!C +---------------+
!C | {v1}= {r}/|r| |
!C +---------------+
!C===
        DNRM20= ZERO
        do ik= 1, N
          iSR= 3*ik-2
          DNRM20= DNRM20 + WW(iSR  ,R)**2 + WW(iSR+1,R)**2 +            &
     &                     WW(iSR+2,R)**2
        enddo
      S_TIME= HECMW_WTIME()
      call HECMW_allREDUCE_DP1 (DNRM20, DNRM2, HECMW_SUM, SOLVER_COMM )
!C        call MPI_allREDUCE (DNRM20, DNRM2, 1, MPI_DOUBLE_PRECISION,     &
!C     &                      MPI_SUM, SOLVER_COMM, ierr)
      E_TIME= HECMW_WTIME()
      COMMtime = COMMtime + E_TIME - S_TIME

        RNORM= dsqrt(DNRM2)
        coef= ONE/RNORM
        do ik= 1, N
          iSR= 3*ik-2
          WW(iSR  ,V)= WW(iSR  ,R) * coef
          WW(iSR+1,V)= WW(iSR+1,R) * coef
          WW(iSR+2,V)= WW(iSR+2,R) * coef
        enddo
!C===

!C
!C +--------------+
!C | {s}= |r|{e1} |
!C +--------------+
!C===
        iSR= 3*1-2
        WW(iSR  ,S) = RNORM         
        WW(iSR+1,S) = ZERO
        WW(iSR+2,S) = ZERO
        do k = 2, N
          kSR= 3*k-2
          WW(kSR  ,S) = ZERO
          WW(kSR+1,S) = ZERO
          WW(kSR+2,S) = ZERO
        enddo
!C===

!C************************************************ GMRES(m) restart
   30   continue
        I   = I    + 1
        ITER= ITER + 1

!C
!C +-------------------+
!C | {w}= [A][Minv]{v} |
!C +-------------------+
!C===
      indexA= ZP
      indexB= ZQ
      indexC= V + I - 1
      call hecmw_solve_precond_33 (indexA, indexB, indexC)

      indexA= ZQ
      indexB= W
      call hecmw_solve_matvec_33  (indexA, indexB)

      S_TIME= HECMW_WTIME()
      call HECMW_SOLVE_SEND_RECV_33                                     &
     &   ( NP , NEIBPETOT, NEIBPE, STACK_IMPORT, NOD_IMPORT,            &
     &     STACK_EXPORT,NOD_EXPORT,WS,WR,WW(1,indexB), SOLVER_COMM,     &
     &     my_rank)
      E_TIME= HECMW_WTIME()
      COMMtime = COMMtime + E_TIME - S_TIME
!C===

!C
!C +------------------------------+
!C | ORTH. BASIS by GRAMM-SCHMIDT |
!C +------------------------------+
!C   Construct the I-th column of the upper Hessenberg matrix H
!C   using the Gram-Schmidt process on V and W.
!C===
      do K= 1, I
        VAL0= 0.d0
        do ik= 1, N
          iSR= 3*ik - 2
          VAL0= VAL0 + WW(iSR  ,W)*WW(iSR  ,V+K-1)                      &
     &               + WW(iSR+1,W)*WW(iSR+1,V+K-1)                      &
     &               + WW(iSR+2,W)*WW(iSR+2,V+K-1)                    
        enddo
      S_TIME= HECMW_WTIME()
      call HECMW_allREDUCE_DP1 (VAL0, VAL, HECMW_SUM, SOLVER_COMM )
!C        call MPI_allREDUCE (VAL0, VAL, 1, MPI_DOUBLE_PRECISION,         &
!C     &                      MPI_SUM, SOLVER_COMM, ierr)
      E_TIME= HECMW_WTIME()
      COMMtime = COMMtime + E_TIME - S_TIME
      
        do ik= 1, N
          iSR= 3*ik - 2
          WW(iSR  ,W)= WW(iSR  ,W) - VAL * WW(iSR  ,V+K-1)
          WW(iSR+1,W)= WW(iSR+1,W) - VAL * WW(iSR+1,V+K-1)
          WW(iSR+2,W)= WW(iSR+2,W) - VAL * WW(iSR+2,V+K-1)
        enddo
        H(K,I)= VAL
      enddo
        
      VAL0= 0.d0
      do ik= 1, N
        iSR= 3*ik - 2
        VAL0= VAL0 + WW(iSR  ,W)**2 + WW(iSR+1,W)**2 + WW(iSR+2,W)**2  
      enddo

      S_TIME= HECMW_WTIME()
      call HECMW_allREDUCE_DP1 (VAL0, VAL, HECMW_SUM, SOLVER_COMM )
!C      call MPI_allREDUCE (VAL0, VAL, 1, MPI_DOUBLE_PRECISION,           &
!C     &                    MPI_SUM, SOLVER_COMM, ierr)
      E_TIME= HECMW_WTIME()
      COMMtime = COMMtime + E_TIME - S_TIME

      H(I+1,I)= dsqrt(VAL)
      coef= ONE / H(I+1,I)
      do ik= 1, N
        iSR= 3*ik - 2
        WW(iSR  ,V+I+1-1)= WW(iSR  ,W) * coef
        WW(iSR+1,V+I+1-1)= WW(iSR+1,W) * coef
        WW(iSR+2,V+I+1-1)= WW(iSR+2,W) * coef
      enddo
!C===

!C
!C +-----------------+
!C | GIVENS ROTARION |
!C +-----------------+
!C===

!C
!C-- Plane Rotation
      do k = 1, I-1 
        VCS= H(k,CS)
        VSN= H(k,SN)
        DTEMP   = VCS*H(k  ,I) + VSN*H(k+1,I)
        H(k+1,I)= VCS*H(k+1,I) - VSN*H(k  ,I)
        H(k  ,I)= DTEMP
      enddo
      
!C
!C-- Construct Givens Plane Rotation
      AA = H(I  ,I)
      BB = H(I+1,I)
      R0= BB
      if (dabs(AA).gt.dabs(BB)) R0= AA
      SCALE= dabs(AA) + dabs(BB)
        
      if (SCALE.ne.0.d0) then
        RR= SCALE * dsqrt((AA/SCALE)**2+(BB/SCALE)**2)
        RR= dsign(1.d0,R0)*RR
        H(I,CS)= AA/RR
        H(I,SN)= BB/RR
       else
        H(I,CS)= 1.d0
        H(I,SN)= 0.d0
        RR     = 0.d0
      endif
     
!C
!C-- Plane Rotation
      VCS= H(I,CS)
      VSN= H(I,SN)
      DTEMP    = VCS*H(I  ,I) + VSN*H(I+1,I)
      H (I+1,I)= VCS*H(I+1,I) - VSN*H(I  ,I)
      H (I  ,I)= DTEMP

      DTEMP    = VCS*WW(I  ,S) + VSN*WW(I+1,S)
      WW(I+1,S)= VCS*WW(I+1,S) - VSN*WW(I  ,S)
      WW(I  ,S)= DTEMP

      RESID = dabs ( WW(I+1,S))/dsqrt(BNRM2)

      if (my_rank.eq.0 .and. ITERlog.eq.1)                              &
     &    write (*, '(2i8, 1pe16.6)') iter,I+1, RESID

      if ( RESID.le.TOL ) then
!C-- [H]{y}= {s_tld}
         do ik= 1, I
           SS(ik)= WW(ik,S)
         enddo
         IROW= I
         WW(IROW,Y)= SS(IROW) / H(IROW,IROW)

         do kk= IROW-1, 1, -1
           do jj= IROW, kk+1, -1
             SS(kk)= SS(kk) - H(kk,jj)*WW(jj,Y)
           enddo
           WW(kk,Y)= SS(kk) / H(kk,kk)
         enddo

!C-- {x}= {x} + {y}{V}
         do kk= 1, N
           kSR= 3*kk-2
           WW(kSR  , AV)= 0.d0
           WW(kSR+1, AV)= 0.d0
           WW(kSR+2, AV)= 0.d0
         enddo

         jj= IROW
         do jj= 1, IROW
         do kk= 1, N
           kSR= 3*kk-2
           WW(kSR  ,AV)= WW(kSR  ,AV) + WW(jj,Y)*WW(kSR  ,V+jj-1)
           WW(kSR+1,AV)= WW(kSR+1,AV) + WW(jj,Y)*WW(kSR+1,V+jj-1)
           WW(kSR+2,AV)= WW(kSR+2,AV) + WW(jj,Y)*WW(kSR+2,V+jj-1)
         enddo
         enddo

         indexA= ZP
         indexB= ZQ
         indexC= AV
         call hecmw_solve_precond_33 (indexA, indexB, indexC)

         do kk= 1, N
           kSR= 3*kk-2
           X(kSR  )= X(kSR  ) + WW(kSR  ,ZQ)
           X(kSR+1)= X(kSR+1) + WW(kSR+1,ZQ)
           X(kSR+2)= X(kSR+2) + WW(kSR+2,ZQ)
         enddo
              
         goto 70                     
      endif                                                         
           
      if ( ITER.gt.MAXIT ) goto 60
      if ( I   .lt.NREST ) goto 30
!C===

!C
!C +------------------+
!C | CURRENT SOLUTION |
!C +------------------+
!C===

!C-- [H]{y}= {s_tld}
      do ik= 1, NREST
        SS(ik)= WW(ik,S)
      enddo
      IROW= NREST
      WW(IROW,Y)= SS(IROW) / H(IROW,IROW)

      do kk= IROW-1, 1, -1
        do jj= IROW, kk+1, -1
          SS(kk)= SS(kk) - H(kk,jj)*WW(jj,Y)
        enddo
        WW(kk,Y)= SS(kk) / H(kk,kk)
      enddo

!C-- {x}= {x} + {y}{V}
      do kk= 1, N
        kSR= 3*kk-2
        WW(kSR  , AV)= 0.d0
        WW(kSR+1, AV)= 0.d0
        WW(kSR+2, AV)= 0.d0
      enddo

      jj= IROW
      do jj= 1, IROW
      do kk= 1, N
        kSR= 3*kk-2
        WW(kSR  ,AV)= WW(kSR  ,AV) + WW(jj,Y)*WW(kSR  ,V+jj-1)
        WW(kSR+1,AV)= WW(kSR+1,AV) + WW(jj,Y)*WW(kSR+1,V+jj-1)
        WW(kSR+2,AV)= WW(kSR+2,AV) + WW(jj,Y)*WW(kSR+2,V+jj-1)
      enddo
      enddo

      indexA= ZP
      indexB= ZQ
      indexC= AV
      call hecmw_solve_precond_33 (indexA, indexB, indexC)

      do kk= 1, N
        kSR= 3*kk-2
        X(kSR  )= X(kSR  ) + WW(kSR  ,ZQ)
        X(kSR+1)= X(kSR+1) + WW(kSR+1,ZQ)
        X(kSR+2)= X(kSR+2) + WW(kSR+2,ZQ)
      enddo

!C
!C-- Compute residual vector R, find norm, then check for tolerance.        
      indexB= R
      call hecmw_solve_init_resid_33 (indexB)

      DNRM20= ZERO
      do ik= 1, N
        kSR= 3*ik - 2
        DNRM20= DNRM20 + WW(kSR  ,R)**2 + WW(kSR+1,R)**2 +              &
     &                   WW(kSR+2,R)**2
      enddo

      S_TIME= HECMW_WTIME()
      call HECMW_allREDUCE_DP1 (DNRM20, DNRM2, HECMW_SUM, SOLVER_COMM )
!C      call MPI_allREDUCE  (DNRM20, DNRM2, 1, MPI_DOUBLE_PRECISION,      &
!C     &                     MPI_SUM, SOLVER_COMM, ierr)
      E_TIME= HECMW_WTIME()
      COMMtime = COMMtime + E_TIME - S_TIME

      WW(I+1,S)= dsqrt(DNRM2/BNRM2)
      RESID    = WW( I+1,S )

!        if ( RESID.le.TOL )   goto 70
      if ( ITER .gt.MAXIT ) goto 60
!C
!C-- RESTART
      goto 10

!C
!C-- iteration FAILED

   60 continue
      ERROR= -300
      INFO = ITER

!C-- [H]{y}= {s_tld}
      do ik= 1, I
        SS(ik)= WW(ik,S)
      enddo
      IROW= I
      WW(IROW,Y)= SS(IROW) / H(IROW,IROW)

      do kk= IROW-1, 1, -1
        do jj= IROW, kk+1, -1
          SS(kk)= SS(kk) - H(kk,jj)*WW(jj,Y)
        enddo
        WW(kk,Y)= SS(kk) / H(kk,kk)
      enddo

!C-- {x}= {x} + {y}{V}
      do kk= 1, N
        kSR= 3*kk-2
        WW(kSR  , AV)= 0.d0
        WW(kSR+1, AV)= 0.d0
        WW(kSR+2, AV)= 0.d0
      enddo

      jj= IROW
      do jj= 1, IROW
      do kk= 1, N
        kSR= 3*kk-2
        WW(kSR  ,AV)= WW(kSR  ,AV) + WW(jj,Y)*WW(kSR  ,V+jj-1)
        WW(kSR+1,AV)= WW(kSR+1,AV) + WW(jj,Y)*WW(kSR+1,V+jj-1)
        WW(kSR+2,AV)= WW(kSR+2,AV) + WW(jj,Y)*WW(kSR+2,V+jj-1)
      enddo
      enddo

      indexA= ZP
      indexB= ZQ
      indexC= AV
      call hecmw_solve_precond_33 (indexA, indexB, indexC)

      do kk= 1, N
        kSR= 3*kk-2
        X(kSR  )= X(kSR  ) + WW(kSR  ,ZQ)
        X(kSR+1)= X(kSR+1) + WW(kSR+1,ZQ)
        X(kSR+2)= X(kSR+2) + WW(kSR+2,ZQ)
      enddo

   70 continue
      E1_TIME= HECMW_WTIME()
      COMPtime= E1_TIME - S1_TIME

      Tsol = COMPtime
      Tcomm= COMMtime

!C
!C-- INTERFACE data EXCHANGE
      call HECMW_SOLVE_SEND_RECV_33                                     &
     &   ( NP,  NEIBPETOT, NEIBPE, STACK_IMPORT, NOD_IMPORT,            &
     &     STACK_EXPORT, NOD_EXPORT, WS, WR, X , SOLVER_COMM,my_rank)

      deallocate (H, WW, WR, WS, SS)

      contains

!C
!C***
!C*** hecmw_solve_init_resid_33
!C***
!C

      subroutine hecmw_solve_init_resid_33 (indexB)
      use hecmw_util
      implicit REAL*8 (A-H,O-Z)      
      integer(kind=kint) :: indexB

      S_TIME= HECMW_WTIME()
      call HECMW_SOLVE_SEND_RECV_33                                     &
     &   ( NP,  NEIBPETOT, NEIBPE, STACK_IMPORT, NOD_IMPORT,            &
     &     STACK_EXPORT, NOD_EXPORT, WS, WR, X , SOLVER_COMM,my_rank)
      E_TIME= HECMW_WTIME()
      COMMtime = COMMtime + E_TIME - S_TIME

      do j= 1, N
          jSR= 3*j-2
          jSB= 9*j-8
           X1= X(jSR  )
           X2= X(jSR+1)
           X3= X(jSR+2)
        WVAL1= B(jSR  ) - D(jSB  )*X1 - D(jSB+1)*X2 - D(jSB+2)*X3
        WVAL2= B(jSR+1) - D(jSB+3)*X1 - D(jSB+4)*X2 - D(jSB+5)*X3
        WVAL3= B(jSR+2) - D(jSB+6)*X1 - D(jSB+7)*X2 - D(jSB+8)*X3
        do k= INL(j-1)+1, INL(j)
             ik= IAL(k)
            kSR= 3*ik- 2
            kSB= 9* k- 8
             X1= X(kSR  )
             X2= X(kSR+1)
             X3= X(kSR+2)
          WVAL1= WVAL1 - AL(kSB  )*X1 - AL(kSB+1)*X2 - AL(kSB+2)*X3
          WVAL2= WVAL2 - AL(kSB+3)*X1 - AL(kSB+4)*X2 - AL(kSB+5)*X3
          WVAL3= WVAL3 - AL(kSB+6)*X1 - AL(kSB+7)*X2 - AL(kSB+8)*X3
        enddo

        do k= INU(j-1)+1, INU(j)
           ik= IAU(k)
            kSR= 3*ik-2
            kSB= 9* k-8
             X1= X(kSR  )
             X2= X(kSR+1)
             X3= X(kSR+2)
          WVAL1= WVAL1 - AU(kSB  )*X1 - AU(kSB+1)*X2 - AU(kSB+2)*X3
          WVAL2= WVAL2 - AU(kSB+3)*X1 - AU(kSB+4)*X2 - AU(kSB+5)*X3
          WVAL3= WVAL3 - AU(kSB+6)*X1 - AU(kSB+7)*X2 - AU(kSB+8)*X3
        enddo

        WW(jSR  ,indexB)= WVAL1
        WW(jSR+1,indexB)= WVAL2
        WW(jSR+2,indexB)= WVAL3
      enddo

      end subroutine hecmw_solve_init_resid_33

!C
!C***
!C*** hecmw_solve_matvec_33
!C***
!C
      subroutine hecmw_solve_matvec_33 (indexA, indexB)
      use hecmw_util
      implicit REAL*8 (A-H,O-Z)      
      integer(kind=kint) :: indexA, indexB

      S_TIME= HECMW_WTIME()
      call HECMW_SOLVE_SEND_RECV_33                                     &
     &   ( NP,  NEIBPETOT, NEIBPE, STACK_IMPORT, NOD_IMPORT,            &
     &     STACK_EXPORT, NOD_EXPORT, WS, WR, WW(1,indexA),              &
     &     SOLVER_COMM,my_rank)
      E_TIME= HECMW_WTIME()
      COMMtime = COMMtime + E_TIME - S_TIME

      do j= 1, N
        jSR= 3*j-2
        jSB= 9*j-8
           X1= WW(jSR  ,indexA)
           X2= WW(jSR+1,indexA)
           X3= WW(jSR+2,indexA)
        WVAL1= D(jSB  )*X1 + D(jSB+1)*X2 + D(jSB+2)*X3
        WVAL2= D(jSB+3)*X1 + D(jSB+4)*X2 + D(jSB+5)*X3
        WVAL3= D(jSB+6)*X1 + D(jSB+7)*X2 + D(jSB+8)*X3
        do k= INL(j-1)+1, INL(j)
           ik= IAL(k)
          kSR= 3*ik-2
          kSB= 9* k-8
          X1= WW(kSR  ,indexA)
          X2= WW(kSR+1,indexA)
          X3= WW(kSR+2,indexA)
          WVAL1= WVAL1 + AL(kSB  )*X1 + AL(kSB+1)*X2 + AL(kSB+2)*X3
          WVAL2= WVAL2 + AL(kSB+3)*X1 + AL(kSB+4)*X2 + AL(kSB+5)*X3
          WVAL3= WVAL3 + AL(kSB+6)*X1 + AL(kSB+7)*X2 + AL(kSB+8)*X3
        enddo
        do k= INU(j-1)+1, INU(j)
           ik= IAU(k)
          kSR= 3*ik-2
          kSB= 9* k-8
          X1= WW(kSR  ,indexA)
          X2= WW(kSR+1,indexA)
          X3= WW(kSR+2,indexA)
          WVAL1= WVAL1 + AU(kSB  )*X1 + AU(kSB+1)*X2 + AU(kSB+2)*X3
          WVAL2= WVAL2 + AU(kSB+3)*X1 + AU(kSB+4)*X2 + AU(kSB+5)*X3
          WVAL3= WVAL3 + AU(kSB+6)*X1 + AU(kSB+7)*X2 + AU(kSB+8)*X3
        enddo

        WW(jSR  ,indexB)= WVAL1
        WW(jSR+1,indexB)= WVAL2
        WW(jSR+2,indexB)= WVAL3
      enddo

      end subroutine hecmw_solve_matvec_33

!C
!C***
!C*** hecmw_solve_precond_33
!C***
!C
      subroutine hecmw_solve_precond_33 (indexA, indexB, indexC)
      use hecmw_util
      implicit REAL*8 (A-H,O-Z)      
      integer(kind=kint) :: indexA, indexB, indexC

      if (PRECOND.eq.1.or.PRECOND.eq.2) then
!C
!C== Block SSOR

      do j= 1, N
        jSR= 3*j-2
        WW(jSR  ,indexA)= WW(jSR  ,indexC)
        WW(jSR+1,indexA)= WW(jSR+1,indexC)
        WW(jSR+2,indexA)= WW(jSR+2,indexC)
      enddo

      do j= 1, NP
        jSR= 3*j-2
        WW(jSR  ,indexB )= 0.d0
        WW(jSR+1,indexB )= 0.d0
        WW(jSR+2,indexB )= 0.d0
      enddo

      do iterPRE= 1, iterPREmax
        do j= 1+N, NP
          jSR= 3*j-2
          WW(jSR  ,indexA)= 0.d0
          WW(jSR+1,indexA)= 0.d0
          WW(jSR+2,indexA)= 0.d0
        enddo

!C
!C-- FORWARD
        do j= 1, N
          jSR= 3*j-2
          jSB= 9*j-8
          SW1= WW(jSR  ,indexA)
          SW2= WW(jSR+1,indexA)
          SW3= WW(jSR+2,indexA)
          isL= INL(j-1)+1
          ieL= INL(j)
          do k= isL, ieL
             ik= IAL(k)
            kSR= 3*ik-2
            kSB= 9* k-8
             X1= WW(kSR  ,indexA)
             X2= WW(kSR+1,indexA)
             X3= WW(kSR+2,indexA)
            SW1= SW1 - AL(kSB  )*X1 - AL(kSB+1)*X2 - AL(kSB+2)*X3 
            SW2= SW2 - AL(kSB+3)*X1 - AL(kSB+4)*X2 - AL(kSB+5)*X3 
            SW3= SW3 - AL(kSB+6)*X1 - AL(kSB+7)*X2 - AL(kSB+8)*X3 
          enddo

          X1= SW1
          X2= SW2
          X3= SW3

          X2= X2 - ALU(jSB+3)*X1
          X3= X3 - ALU(jSB+6)*X1 - ALU(jSB+7)*X2
          X3= ALU(jSB+8)*  X3
          X2= ALU(jSB+4)*( X2 - ALU(jSB+5)*X3 )
          X1= ALU(jSB  )*( X1 - ALU(jSB+2)*X3 - ALU(jSB+1)*X2)

          WW(jSR  ,indexA)= X1
          WW(jSR+1,indexA)= X2
          WW(jSR+2,indexA)= X3
        enddo

!C
!C-- BACKWARD

        do j= N, 1, -1
          jSR= 3*j-2
          jSB= 9*j-8

          isU= INU(j-1) + 1
          ieU= INU(j) 
          SW1= 0.d0
          SW2= 0.d0
          SW3= 0.d0
          do k= isU, ieU
             ik= IAU(k)
            kSR= 3*ik-2
            kSB= 9* k-8
             X1= WW(kSR  ,indexA)
             X2= WW(kSR+1,indexA)
             X3= WW(kSR+2,indexA)
            SW1= SW1 + AU(kSB  )*X1 + AU(kSB+1)*X2 + AU(kSB+2)*X3
            SW2= SW2 + AU(kSB+3)*X1 + AU(kSB+4)*X2 + AU(kSB+5)*X3
            SW3= SW3 + AU(kSB+6)*X1 + AU(kSB+7)*X2 + AU(kSB+8)*X3
          enddo

          X1= SW1
          X2= SW2
          X3= SW3
          X2= X2 - ALU(jSB+3)*X1
          X3= X3 - ALU(jSB+6)*X1 - ALU(jSB+7)*X2
          X3= ALU(jSB+8)*  X3
          X2= ALU(jSB+4)*( X2 - ALU(jSB+5)*X3 )
          X1= ALU(jSB  )*( X1 - ALU(jSB+2)*X3 - ALU(jSB+1)*X2)
          WW(jSR  ,indexA)=  WW(jSR  ,indexA) - X1
          WW(jSR+1,indexA)=  WW(jSR+1,indexA) - X2
          WW(jSR+2,indexA)=  WW(jSR+2,indexA) - X3
        enddo

!C
!C-- additive Schwartz

      S_TIME= HECMW_WTIME()
        call HECMW_SOLVE_SEND_RECV_33                                   &
     &     ( NP , NEIBPETOT, NEIBPE, STACK_IMPORT, NOD_IMPORT,          &
     &       STACK_EXPORT, NOD_EXPORT, WS, WR, WW(1,indexA) ,           &
     &       SOLVER_COMM,  my_rank)
      E_TIME= HECMW_WTIME()
      COMMtime = COMMtime + E_TIME - S_TIME

      do j= 1, NP
        jSR=  3*j- 2
        WW(jSR  ,indexB)= WW(jSR  ,indexB) + WW(jSR  ,indexA)         
        WW(jSR+1,indexB)= WW(jSR+1,indexB) + WW(jSR+1,indexA)         
        WW(jSR+2,indexB)= WW(jSR+2,indexB) + WW(jSR+2,indexA)         
      enddo

      if (iterPRE.eq.iterPREmax) goto 760

      do j= 1, N
        jSR= 3*j-2
        jSB= 9*j-8
           X1= WW(jSR  ,indexB)
           X2= WW(jSR+1,indexB)
           X3= WW(jSR+2,indexB)
        WVAL1= WW(jSR  ,indexC)                                         &
     &           - D(jSB  )*X1 - D(jSB+1)*X2 - D(jSB+2)*X3           
        WVAL2= WW(jSR+1,indexC)                                         &
     &           - D(jSB+3)*X1 - D(jSB+4)*X2 - D(jSB+5)*X3           
        WVAL3= WW(jSR+2,indexC)                                         &
     &           - D(jSB+6)*X1 - D(jSB+7)*X2 - D(jSB+8)*X3           
        do k= INL(j-1)+1, INL(j)
          ik = IAL(k)
          kSR= 3*ik-2
          kSB= 9* k-8
           X1= WW(kSR  ,indexB)
           X2= WW(kSR+1,indexB)
           X3= WW(kSR+2,indexB)
          WVAL1= WVAL1 - AL(kSB  )*X1 - AL(kSB+1)*X2 - AL(kSB+2)*X3 
          WVAL2= WVAL2 - AL(kSB+3)*X1 - AL(kSB+4)*X2 - AL(kSB+5)*X3 
          WVAL3= WVAL3 - AL(kSB+6)*X1 - AL(kSB+7)*X2 - AL(kSB+8)*X3 
        enddo

        do k= INU(j-1)+1, INU(j)
          ik = IAU(k)
          kSR= 3*ik-2
          kSB= 9* k-8
           X1= WW(kSR  ,indexB)
           X2= WW(kSR+1,indexB)
           X3= WW(kSR+2,indexB)
          WVAL1= WVAL1 - AU(kSB  )*X1 - AU(kSB+1)*X2 - AU(kSB+2)*X3
          WVAL2= WVAL2 - AU(kSB+3)*X1 - AU(kSB+4)*X2 - AU(kSB+5)*X3
          WVAL3= WVAL3 - AU(kSB+6)*X1 - AU(kSB+7)*X2 - AU(kSB+8)*X3
        enddo
        
        WW(jSR  , indexA)= WVAL1
        WW(jSR+1, indexA)= WVAL2
        WW(jSR+2, indexA)= WVAL3
      enddo
 
 760  continue


      enddo
      endif

      if (PRECOND.eq.3) then
!C
!C== Block SCALING

      do j= 1, N
        jSR= 3*j-2
        jSB= 9*j-8

        X1= WW(jSR  ,indexC)
        X2= WW(jSR+1,indexC)
        X3= WW(jSR+2,indexC)

        X2= X2 - ALU(jSB+3)*X1
        X3= X3 - ALU(jSB+6)*X1 - ALU(jSB+7)*X2
        X3= ALU(jSB+8)*  X3
        X2= ALU(jSB+4)*( X2 - ALU(jSB+5)*X3 )
        X1= ALU(jSB  )*( X1 - ALU(jSB+2)*X3 - ALU(jSB+1)*X2)
        WW(jSR  ,indexB)= X1
        WW(jSR+1,indexB)= X2
        WW(jSR+2,indexB)= X3
      enddo
      endif

      end subroutine hecmw_solve_precond_33

      end subroutine  hecmw_solve_GMRES_33
      end module     hecmw_solver_GMRES_33
