!-------------------------------------------------------------------------------
! Copyright (c) 2016 The University of Tokyo
! This software is released under the MIT License, see LICENSE.txt
!-------------------------------------------------------------------------------
!> This module provides a function to control eigen analysis
module m_fstr_solve_eigen
  contains

!> SOLVE EIGENVALUE PROBLEM
  subroutine fstr_solve_eigen( hecMESH, hecMAT, fstrEIG, fstrSOLID, &
                             & fstrRESULT, fstrPARAM, fstrMAT)
    use hecmw_util
    use m_fstr
    use m_fstr_StiffMatrix
    use m_fstr_AddBC
    use m_fstr_EIG_setMASS
    use m_fstr_EIG_lanczos
    use m_fstr_EIG_output
    use m_static_lib
    use m_hecmw2fstr_mesh_conv
    use fstr_matrix_con_contact

    implicit none

    type(hecmwST_local_mesh ) :: hecMESH
    type(hecmwST_matrix     ) :: hecMAT
    type(fstr_solid         ) :: fstrSOLID
    type(hecmwST_result_data) :: fstrRESULT
    type(fstr_param         ) :: fstrPARAM
    type(fstr_eigen         ) :: fstrEIG
    type(fstrST_matrix_contact_lagrange) :: fstrMAT

    real(kind=kreal) :: t1, t2

    t1 = hecmw_Wtime()

    fstrSOLID%dunode = 0.0d0
    call fstr_StiffMatrix( hecMESH, hecMAT, fstrSOLID, 0.0d0, 0.0d0 )

    call fstr_AddBC(1,  hecMESH, hecMAT, fstrSOLID, fstrPARAM, fstrMAT, 2)

    call setMASS(fstrSOLID, hecMESH, hecMAT, fstrEIG)

    call fstr_solve_lanczos(hecMESH, hecMAT, fstrSOLID, fstrEIG)

    call fstr_eigen_output(hecMESH, hecMAT, fstrEIG)

    call fstr_eigen_make_result(hecMESH, hecMAT, fstrEIG, fstrRESULT)

    t2 = hecmw_Wtime()

    IF(myrank == 0)THEN
      WRITE(IMSG,'("### FSTR_SOLVE_EIGEN FINISHED!")')
      WRITE(*,'("### FSTR_SOLVE_EIGEN FINISHED!")')
    endif

  end subroutine fstr_solve_eigen

end module m_fstr_solve_eigen
