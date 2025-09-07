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
c						
c	WRAPPER FUNCTION for RANDOM_NUMBER
c
c ----------------------------------------------------------------------------
      FUNCTION ran3(idum)
      INTEGER idum
      REAL*4 ran3, x

      CALL RANDOM_NUMBER(x)

      ran3=x

      return
      END
c
c ----------------------------------------------------------------------------
c
