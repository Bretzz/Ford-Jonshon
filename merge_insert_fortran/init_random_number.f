c***************************************************************************
c**
c**  This file is part of 1D-LOC-DASPEX project
c**
c**  1D-LOC-DASPEX is free software: you can redistribute it and/or modify
c**  it under the terms of the GNU General Public License as published by
c**  the Free Software Foundation, either version 3 of the License, or
c**  (at your option) any later version.
c**
c**  1D-LOC-DASPEX is distributed in the hope that it will be useful,
c**  but WITHOUT ANY WARRANTY; without even the implied warranty of
c**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
c**  GNU General Public License for more details.
c**
c**  You should have received a copy of the GNU General Public License
c**  along with the code.  If not, see <http://www.gnu.org/licenses/>
c**
c**  See also https://gitlab.com/rjmcmc-1D-geophysics/1d-loc-daspex
c**
c**  Created: 2023-11-01
c**  Copyright: 2023-2032
c**    Nicola Piana Agostinetti
c**
c***************************************************************************/

        subroutine init_random_number(state0)


        implicit none
        integer :: state_size, i, state0
        integer, allocatable, dimension(:) :: state
        real :: ran, oldran

        call random_seed( size=state_size )
        allocate(state(state_size))

        state = state0
        call random_seed( put=state )

        ran = 0.0
        do i=1,100
          oldran = ran
          call random_number(ran)
c          write(*,'(a,i3,2f12.6)') 'RANDOM_INIT:: iter, ran, diff: ', i, ran, ran-oldran
        enddo

        return
        end

