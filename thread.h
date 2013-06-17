#ifndef THREAD_H_1356505929_76
#define THREAD_H_1356505929_76
/**
 * File: thread.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 15:12:09.756000
 * Written In: Peking University, beijing, China
 */

#include "utils.h"

#ifdef OS_WIN32
#include <process.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

class thread {
protected:
#ifdef OS_WIN32
	HANDLE            myThread;
	CRITICAL_SECTION  critSec;  	//same as a mutex
#else
	pthread_t        myThread;
	pthread_mutex_t  myMutex;
#endif
	bool running;
	bool blocking;
	
public:
	thread();
	virtual ~thread();
	
	bool isrunning() const { return running; }
	bool start(bool blocking=false, bool verbose=true);
	bool lock();
	bool unlock();
	void stop();

protected:
	virtual void run();
#ifdef OS_WIN32
	static unsigned int __stdcall run(void * ptr);
#else
	static void* run(void * ptr);
#endif
};

#endif /* THREAD_H_1356505929_76 */
