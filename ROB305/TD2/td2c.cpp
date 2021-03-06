#include <iostream>
#include <time.h>
#include <sstream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>

//global variable
int nLoops = 0;
double pCounter = 0.0;
int mutexSignal = 0;
pthread_mutex_t mutex;

void incr(unsigned int nLoops, double* pCounter){
 	for(unsigned int i=0;i<nLoops;i++){
 		*pCounter += 1.0;
 	}
}

void* call_incr(void* agr){
	if (mutexSignal ==0)
		incr(nLoops,&pCounter);
	else{
		pthread_mutex_lock(&mutex);
		incr(nLoops,&pCounter);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(int argc, char* argv[]){

	if(argc < 4){
		std::cerr<<"Usage:please add parameter:nLoop,nTasks and mutex signal(1:true,0:false)"<<std::endl;
		return 1;
	}

	unsigned int nTasks = (int)*argv[2];
	pthread_t mythread[nTasks];	
	timespec start,end,time;
	//schedule parameter
	struct sched_param param;
	int policy = SCHED_RR;

	nLoops = (int)* argv[1];
    mutexSignal = (int)* argv[3];

    //init mutex
    pthread_mutex_init(&mutex,NULL);
    
	//start timing
	clock_gettime(CLOCK_REALTIME,&start);
	//task work
	for(unsigned int i = 0;i<nTasks;i++){
		if ( pthread_create(&mythread[i], NULL, call_incr, NULL) ) {
		    printf("error creating thread.");
		    return 1;
		}
		param.sched_priority = sched_get_priority_max(policy)-i;
		pthread_setschedparam(pthread_self(),SCHED_RR,&param);
		if ( pthread_join (mythread[i], NULL ) ) {
		    printf("error join thread.");
		    return 1;
		}
	}
	//end timing
	clock_gettime(CLOCK_REALTIME,&end);

	//calculate time
	if(end.tv_nsec<start.tv_nsec){
		time.tv_sec = end.tv_sec - 1 -start.tv_sec;
		time.tv_nsec = end.tv_nsec + 1000000000 - start.tv_nsec;
	}
	else{
		time.tv_sec = end.tv_sec  -start.tv_sec;
		time.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	printf("Counter=%f\n",pCounter);
	printf("time is %ld s, %ld ns\n",time.tv_sec,time.tv_nsec);

	return 0;
}
