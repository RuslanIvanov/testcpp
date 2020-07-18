
#include <iostream>
#include "c_event.h"
#include "debugPrint.h"
//using namespace std;

cEvent::cEvent(void):m_bCreated(true)
{
	pthread_mutexattr_t mattr;

	pthread_mutexattr_init(&mattr);
	pthread_mutex_init(&m_lock,&mattr);
	pthread_cond_init(&m_ready,NULL);
	
	m_param  = 0;
}

cEvent::~cEvent(void)
{
	pthread_cond_destroy(&m_ready);
	pthread_mutex_destroy(&m_lock);
	m_param=0;
}

/**
 *
 * Set
 * set an event to signaled
 *
 **/
void cEvent::Set(unsigned int param)
{
	/*
	  разблокирует ожидающий данную условную переменную поток. Если сигнала 
	  по условной переменной ожидают несколько потоков,
	  то будет разблокирован только какой-либо один из них.
	*/
    m_param = param;
    //printf("\nset param %x [%p]",m_param,(void*)m_param);
    //--
    pthread_mutex_lock(&m_lock);
    //--
    pthread_cond_signal(&m_ready);
    //--
    pthread_mutex_unlock(&m_lock);
    //--
}

/**
 *
 * Wait
 * wait for an event -- wait for an event object
 * to be set to signaled.  must be paired with a
 * call to reset within the same thread.
 *
 **/
bool
cEvent::Wait(unsigned int *pparam)
{
	try
	{	/*
		автоматически освобождает взаимоисключающую блокировку, указанную m_lock, 
		а вызывающий поток блокируется по условной переменной, заданной m_ready. 
		Заблокированный поток разблокируется функциями pthread_cond_signal() и 
		pthread_cond_broadcast(). Одной условной переменной могут быть 
		заблокированы несколько потоковwait.
		*/
		pthread_mutex_lock(&m_lock);
		pthread_cond_wait(&m_ready,&m_lock);

        //--
        //pthread_mutex_unlock(&m_lock);//если автоматичекий сброс события

		//printf("\nWait param %x [%p]",m_param,(void*)m_param);
        *pparam = m_param;
        return true;
	}
	catch( char *psz )
	{
        ERRORP(("\nSCVS_EVENT: Fatal exception  cEvent::Wait: %s", psz));
	}
    return true;
}

/**
 *
 * Reset
 * reset an event flag to unsignaled
 * wait must be paired with reset within the same thread.
 *
 **/
void cEvent::Reset()
{
    m_param=0;//???
	try 
	{
        pthread_mutex_unlock(&m_lock);
	}
	catch( char *psz )
	{
        ERRORP(("Fatal exception  cEvent::Reset: %s", psz));

	}
}

