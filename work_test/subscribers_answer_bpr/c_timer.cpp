#include "c_timer.h"

cTimer::cTimer(int t)
{   //если m_t = 0, то таймер не взводится
    m_t = t;
}

int cTimer::setTimer( void (*pFunc)(int))
{//0 - успешно, 1 - плохо. 

	if(pFunc == NULL) return 1;
	
	signal(SIGALRM,pFunc);
	
	m_timer.it_value.tv_sec=0;
	m_timer.it_value.tv_usec = m_t*1000;
	
	m_timer.it_interval.tv_sec=0;
        m_timer.it_interval.tv_usec = m_t*1000;

        return (setitimer(ITIMER_REAL,&m_timer,NULL));
}
