c
c
c ----------------------------------------------------------------------------
c                                                                             
c       cputime - calls system dependent routine to calculate cputime.
c                                                            
c                                                                             
c                                         N. Piana Agostinetti, March 2011       
c                                                                             
c ----------------------------------------------------------------------------
c                                                                             
        subroutine cputime(t2)                

        real*8 t2
        integer count_1, count_rate, count_max

        call system_clock(count_1, count_rate, count_max)

        t2 = (1.d0*count_1)/(1.d0*count_rate) 

        return
        end   



c

