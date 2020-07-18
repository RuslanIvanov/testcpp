#ifndef C_TIMERRT
#define C_TIMERRT

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//#include <unistd.h>

class cTimerrt
{
private:
	/*struct itimerval m_timer;*/
	sigevent m_se;
	itimerspec m_tv;
	timer_t m_tt;

	int m_nsec;
	int m_usec;
	int m_sec;
public: 
	cTimerrt(int t = 0);
	int setTimerrt(void (*pFunc)(sigval));
	void setInterval(int,int,int);
};

#endif
