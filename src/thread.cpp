/**
 * File: thread.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 15:12:16.838000
 * Written In: Peking University, beijing, China
 */
 
#include "thread.h"

thread::thread() {
	running = false;
#ifdef OS_WIN32
	InitializeCriticalSection(&critSec);
#else
	pthread_mutex_init(&myMutex, NULL);
#endif
}

thread::~thread() {
#ifndef OS_WIN32
	pthread_mutex_destroy(&myMutex);
#endif
	if (running) stop();
}

// bool isrunning() const { return running; }

bool thread::start(bool blocking, bool verbose) {
	if (running) {
		magic("thread: thread already running\n");
		return false;
	}
	// have to put this here because the thread can be running
	// before the call to create it returns
	running   = true;
#ifdef OS_WIN32
	// InitializeCriticalSection(&critSec);
	// unsigned long _beginthreadex(
		// void *security,
		// unsigned stack_size,
		// unsigned ( __stdcall *start_address )( void * ),
		// void *arglist,
		// unsigned initflag,
		// unsigned *thrdaddr
	// );
	myThread = (HANDLE)_beginthreadex(NULL, 0, this->run,  (void *)this, 0, NULL);
#else
	// pthread_mutex_init(&myMutex, NULL);
	pthread_create(&myThread, NULL, run, (void *)this);
#endif
	this->blocking=blocking;
	return true;
}

bool thread::lock() {	//returns false if it can't lock
#ifdef OS_WIN32
	if (blocking) EnterCriticalSection(&critSec);
	else {
		if (!TryEnterCriticalSection(&critSec)) {
			magic("thread: mutext is busy \n");
			return false;
		}
	}
	magic("thread: we are in -- mutext is now locked \n");
#else
	if (blocking) {
		magic("thread: waiting till mutext is unlocked\n");
		pthread_mutex_lock(&myMutex);
		magic("thread: we are in -- mutext is now locked \n");
	} else {
		int value=pthread_mutex_trylock(&myMutex);
		if (value==0) {
			magic("thread: we are in -- mutext is now locked \n");
		}
		else {
			magic("thread: mutext is busy - already locked\n");
			return false;
		}
	}
#endif
	return true;
}

bool thread::unlock() {
#ifdef OS_WIN32
	LeaveCriticalSection(&critSec);
#else
	pthread_mutex_unlock(&myMutex);
#endif
	magic("thread: we are out -- mutext is now unlocked \n");
	return true;
}

void thread::stop() {
	if (running) {
		running=false;
#ifdef OS_WIN32
		CloseHandle(myThread);
#else
		pthread_detach(myThread);
#endif
		magic("thread: thread stopped\n");
	} else {
		magic("thread: thread already stopped\n");
	}
}

void thread::run() {
	magic("thread: please overide this run method for thead main code\n");
}

#ifdef OS_WIN32
unsigned int __stdcall thread::run(void * ptr) {
	thread* me=(thread*)ptr;
	me->run();
	me->stop();
	return 0;
}
#else
void* thread::run(void * ptr) {
	thread* me=(thread*)ptr;
	me->run();
	me->stop();
	return 0;
}
#endif
