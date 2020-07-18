#include "c_timersys.h"

cTimerrt::cTimerrt(int t)
{   	//если m_t = 0, то таймер не взводится
	m_nsec = t*1000*1000;
	
	m_sec = 0;
	m_usec = 0;
	//m_nsec = 0;

	memset(&m_se, 0, sizeof(m_se));
	memset(&m_tv, 0, sizeof(m_tv));
	memset(&m_tt, 0, sizeof(m_tt));
}

void cTimerrt::setInterval(int sec, int usec, int nsec)
{
	m_sec = sec;
	m_usec = usec;
	m_nsec = nsec;
}

int cTimerrt::setTimerrt(void (*pFunc)(sigval sv))
{//0 - успешно, -1 - плохо. 
        int rez = 0;
	if(pFunc == NULL) { printf("\n #Error1 cTimerrt::setTimer"); return 1; }

	m_se.sigev_notify = SIGEV_THREAD;
        m_se.sigev_signo = 1;
        m_se.sigev_notify_function = pFunc;
        m_se.sigev_value.sival_int = 1;

        rez =  timer_create(CLOCK_REALTIME/*CLOCK_MONOTONIC*/,&m_se,&m_tt);

        m_tv.it_interval.tv_sec = m_sec;
        //m_tv.it_interval.tv_usec = m_usec;
        m_tv.it_interval.tv_nsec = m_nsec;
        
        m_tv.it_value.tv_sec = m_sec;
        //m_tv.it_value.tv_usec = m_usec;
        m_tv.it_value.tv_nsec = m_nsec;

        rez = timer_settime(m_tt, 0, &m_tv, NULL); // относительный таймер

        return rez;
}
