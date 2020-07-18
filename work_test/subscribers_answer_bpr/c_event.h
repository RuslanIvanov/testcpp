// класс события, принимает значение m_param
#ifndef C_EVENT
#define C_EVENT

//#include <stdio.h>
//#include <pthread.h>
//#include <unistd.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

#include "globals.h"

class cEvent
{
private:
	int m_id;
	unsigned int m_param;
	
	pthread_cond_t m_ready;
	pthread_mutex_t m_lock;

public:
	bool m_bCreated;
	void Set(unsigned int);
	bool Wait(unsigned int*);
	void Reset();
	cEvent(void);
	~cEvent(void);
};

#endif

