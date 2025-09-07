
	subroutine binary_insert(x,n_int,N,starting_elements,seq,kk,inserted)

	implicit none

        include 'sort.param'

c Variables

	integer x
	integer n_int
	integer N
	integer starting_elements
	integer seq(max_n)
	integer kk

	logical inserted

c Scratch variables

	integer i, order_n
	integer first_element, last_element, mid_element
	
	logical last_iter

	kk=-1

c Defing max number of divisions

	order_n=int(log(1.0*starting_elements)/log(2.0))+2

c Exiting IF smaller than first element

        if(x.lt.seq(n_int)) goto 2002

c Binary sorting

        first_element=1
        last_element=starting_elements
	
	last_iter=.false.
 	
        do i=1,order_n

          if(last_element-first_element.eq.1)last_iter=.true.

          mid_element=int((last_element+first_element)/2)
	  kk = (mid_element)*n_int

c	  write(*,*) ' Sorting:', x, order_n, i, first_element, last_element, mid_element 

	  if(x.gt.seq(kk))then
            first_element=mid_element
          else
            last_element=mid_element
          endif

	  if(last_iter)goto 2001

	enddo

	write(*,*) 'ERROR:: ', first_element, last_element, x, seq(kk)
	STOP ' - exit w/ error in Divide-and-Conquer routine'

 2001   continue

        inserted=.true.

	return

 2002   continue

        inserted=.false.

	return
	end

