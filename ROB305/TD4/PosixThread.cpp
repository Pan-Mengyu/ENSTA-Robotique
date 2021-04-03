#include "PosixThread.h"
#include <unistd.h>
#include "timespec.h"
PosixThread::PosixThread(){
	posixId = 0;
	pthread_attr_init(&posixAttr);
	pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);
}

PosixThread::PosixThread(pthread_t posixId){
	posixId = posixId;
	pthread_attr_init(&posixAttr);
	pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);
	sched_param schedParam;
	int get_policy;
	int get_param = pthread_getschedparam(posixId, &get_policy, &schedParam);
	if (get_param == ESRCH){
		throw(Exception("ERROR: The thread dose not exist"));
	}
	pthread_attr_setschedpolicy(&posixAttr, get_policy);
	pthread_attr_setschedparam(&posixAttr, &schedParam);
}

PosixThread::~PosixThread(){
	pthread_attr_destroy(&posixAttr);
}

void PosixThread::start(void *(*threadFunc)(void *),void* threadArg){
	pthread_create(&posixId,&posixAttr,threadFunc,threadArg);
	isActive = true;
}

void PosixThread::join(){
	void* status;
	pthread_join(posixId, &status);
}

bool PosixThread::join(double timeout_ms){
	void* status;
	timespec t = timespec_from_ms(timeout_ms);
	return pthread_timedjoin_np((this -> posixId), &status, &t);
}

bool PosixThread::setScheduling(int schedPolicy,int priority){
	struct sched_param sched;
	sched.sched_priority = priority; 
	if(isActive){
        pthread_setschedparam(posixId, schedPolicy, &sched);
        return true;
    }
    else{
        pthread_attr_setschedpolicy(&posixAttr, schedPolicy);
        pthread_attr_setschedparam(&posixAttr, &sched);
        return false;
    }
}

bool PosixThread::getScheduling(int* schedPolicy,int* priority){
	struct sched_param sched;
	*priority = sched.sched_priority;
	if(isActive){
	    pthread_getschedparam(posixId, schedPolicy, &sched);
	    return true;
	}
	else{
	    pthread_attr_getschedpolicy(&posixAttr, schedPolicy);
	    pthread_attr_getschedparam(&posixAttr, &sched);
	    return false;
	}
}

PosixThread::Exception::Exception(const string& msg)
{
	error_message = msg;
}

Thread::Thread(){
	
}

Thread::~Thread(){
	
}

void Thread::start(){
	if (!isStarted){
		isStarted = true;
		chrono.restart();
		PosixThread::start(call_run, this);
		chrono.stop();
	}
}

void Thread::sleep_ms(double delay_ms){
    timespec_wait(timespec_from_ms(delay_ms));
}

double Thread::startTime_ms(){
    return chrono.startTime();
}

double Thread::stopTime_ms(){
    return chrono.stopTime();
}

double Thread::execTime_ms(){
    return (chrono.stopTime() - chrono.startTime());
}

void* Thread::call_run(void* v_thread){
    Thread* p_thread = (Thread*) v_thread;
	p_thread->run();
    return p_thread;
}

//only for the test to re-do the TD2-a
void Thread:: run(){
	for( int i=0;i<nLoops;i++){
 		pCounter += 1.0;
 	}
}
