!======================================================================!
!                                                                      !
! Software Name : FrontISTR Ver. 3.2                                   !
!                                                                      !
!      Module Name : m_solve_LINEQ_mkl                                 !
!                                                                      !
!            Written by Z. Sun(ASTOM)                                  !
!                                                                      !
!                                                                      !
!      Contact address :  IIS,The University of Tokyo, CISS            !
!                                                                      !
!      "Structural Analysis for Large Scale Assembly"                  !
!                                                                      !
!======================================================================!
!======================================================================!
!
!> \brief This module provides functions to solve sparse system of 
!> \linear equitions using intel MKL direct sparse solver 
!>
!>  \author     Z. Sun(ASTOM)
!>  \date       2010/11   
!>  \version    0.00
!!
!======================================================================!

module m_solve_LINEQ_mkl         


   use m_fstr                                                  
   use m_set_arrays_directsolver_contact              

   implicit none
!< ------------------------------------------------ input parameters for MKL solver(see Intel(R) MKL Reference Manual)
   integer(kind=8)               :: pt(64)                 
   integer (kind=kint)           :: maxfct
   integer (kind=kint)           :: mnum
   integer (kind=kint)           :: mtype
   integer (kind=kint)           :: phase        
   integer (kind=kint)           :: nrhs
   integer (kind=kint)           :: msglvl   
   integer (kind=kint)           :: iparm(64)
   real     (kind=kreal)          :: dparm(64)      	  
!< ----------------------------------------------- input parameters for MKL solver

  contains  


!> \brief This subroutine executes phase 11 of intel MKL solver  
!> \(see Intel(R) MKL Reference Manual)
    subroutine initialize_solver_mkl(hecMAT,fstrMAT)                
  
      type (hecmwST_matrix)                    :: hecMAT       !< type hecmwST_matrix
      type (fstrST_matrix_contact_lagrange)    :: fstrMAT      !< type fstrST_matrix_contact_lagrange
     
      integer(kind=kint)                       :: ntdf         !< total degree of freedom
      integer(kind=kint)                       :: idum, ierr
      real(kind=kreal)                          :: ddum
                    
        ntdf = hecMAT%NP*hecMAT%NDOF + fstrMAT%num_lagrange

        maxfct = 1; mnum = 1; nrhs = 1                                                        
        iparm = 0                                                                  
        iparm(1)  = 1; iparm(2)  = 2; iparm(3)  = 1; iparm(10) = 13    
        iparm(11) = 1; iparm(13) = 1; iparm(18) =-1; iparm(19) =-1         
                                      
        if( symmetricMatrixStruc )then                                            
          mtype = -2
        else
          mtype = 11                
        endif 
        msglvl = 0 
        ierr = 0                                                                      
          
        phase = 11 
        call pardiso(pt, maxfct, mnum, mtype, phase, ntdf, values, pointers, indices, &                                 
                     idum, nrhs, iparm, msglvl, ddum, ddum, ierr)
        if(ierr /= 0) then
          write(*,'(" initialize_solver_mkl: ERROR was detected in phase", 2I2)') phase,ierr 
          stop
        endif
         
        deallocate(values)
         
    end subroutine initialize_solver_mkl
    
 
!> \brief This subroutine executes phase 22 and phase 33 of the MKL solver
!> \(see Intel(R) MKL Reference Manual)  
    subroutine solve_LINEQ_mkl(hecMAT,fstrMAT)          
  
      type (hecmwST_matrix)                    :: hecMAT         !< type hecmwST_matrix
      type (fstrST_matrix_contact_lagrange)    :: fstrMAT        !< type fstrST_matrix_contact_lagrange
      integer(kind=kint)                       :: ntdf           !< total degree of freedom              
      integer(kind=kint)                       :: idum, ierr
      real(kind=kreal)                          :: ddum     
      real(kind=kreal), allocatable            :: x(:)           !< solution vector
         
      ntdf = hecMAT%NP*hecMAT%NDOF + fstrMAT%num_lagrange

      phase = 22  
      call pardiso(pt, maxfct, mnum, mtype, phase, ntdf, values, pointers, indices,idum,   &
                   nrhs, iparm, msglvl, ddum, ddum, ierr)
        if(ierr /= 0) then
          write(*,'(" solve_LINEQ_mkl: [Error] was detected in phase ", 2I2)')phase,ierr  
          stop
        endif
        write(*,*) ' [Pardiso_MKL]: Factorization completed ! '

        allocate(x(size(hecMAT%X)))                                      
        x = 0.0d0 

        iparm(8) = 6        
        phase = 33
        call pardiso(pt, maxfct, mnum, mtype, phase, ntdf, values, pointers, indices, idum,  &
                     nrhs, iparm, msglvl, hecMAT%B, X, ierr)                 
          if(ierr /= 0) then
            write(*,'(" solve_LINEQ_mkl: [Error] was detected in phase ", 2I2)')phase,ierr  
            stop
          endif
        write(*,*) ' [Pardiso_MKL]: Solve completed ... '

        hecMAT%X = x                                                    

        deallocate(x)                      
    
    end subroutine solve_LINEQ_mkl
    

end module m_solve_LINEQ_mkl
