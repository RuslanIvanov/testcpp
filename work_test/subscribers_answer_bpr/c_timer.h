#ifndef C_TIMER
#define C_TIMER

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

class cTimer
{
private:
	struct itimerval m_timer;
	int m_t;
public: 
	cTimer(int t = 0);
	int setTimer( void (*pFunc)(int));
};

#endif