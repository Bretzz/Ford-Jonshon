
	program test_binary_nsert

	implicit none

c Variables

        integer x
        integer n_int
        integer N
        integer starting_elements
        integer seq(1000)
        integer kk

        logical inserted


	x=94
	n_int=2
	N=100
        starting_elements=11

	inserted=.false.
        kk=-1

	seq(2)=21
	seq(4)=25
        seq(6)=37
        seq(8)=44
        seq(10)=51
        seq(12)=52
        seq(14)=68
        seq(16)=78
        seq(18)=81
        seq(20)=95
        seq(22)=96




        call binary_insert(x,n_int,N,starting_elements,seq,kk,inserted)

	write(*,*) ' SORTING: ', x, kk, inserted


	stop
	end
