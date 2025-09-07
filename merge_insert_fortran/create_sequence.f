c
c
c  Create a sequence of N integer -- also N is random
c
c
c


	program create_sequence


	implicit none


c  Variables

	integer iseed0	

c Maximum value for the integer in the sequence

	integer max_integer
	parameter(max_integer=500000)

c MIN/MAX number of integer in the sequence

	integer min_n, max_n
	parameter(min_n=100000, max_n=100000)

c Number of integers in the sequence

	integer n 

c Sequence

	integer seq(max_n)

c Scratch variables

	integer i, j, k, test
	real*4 p, ran3
	logical REPEAT

c
c ------------------------------------------------------------
c ------------------------------------------------------------
c
c  Define random seed for RANDOM_NUMBER
c
        iseed0=123459
        call init_random_number(iseed0)

c
c ------------------------------------------------------------
c ------------------------------------------------------------
c

c Define N

	p=ran3(iseed0)
	N=min_n+int(p*(max_n-min_n))

	write(*,*) ' Selected a sequence of ', N, ' integers '


c Define sequence

	do i=1, N

	  do k=1,1000

	    REPEAT=.false.
	    p=ran3(iseed0)
	    test=int(p*max_integer)+1
            do j=1,N-1
	      if(test.eq.seq(j)) REPEAT=.true.
            enddo
            if(.not.REPEAT) goto 1001

          enddo
	  STOP ' REPETITION'
 1001     continue
	  seq(i)=test
	  write(*,*) i, seq(i)

	enddo

c Write sequence

	open(11,file='sequence', status='unknown')
	write(11,'(i10)') N
	do i = 1, N
	  write(11,'(2i8)') i, seq(i)
        enddo
	close(11)



	stop
	end
