#include <iostream>
#include <time.h>
#include <sstream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int nLoops = 0;
double pCounter = 0.0;

void incr(unsigned int nLoops, double* pCounter){
 	for(unsigned int i=0;i<nLoops;i++){
 		*pCounter += 1.0;
 	}
}

void* call_incr(void* agr){
	incr(nLoops,&pCounter);
	return NULL;
}

int main(int argc, char* argv[]){

	if(argc < 3){
		std::cerr<<"Usage:please add parameter:nLoop,nTasks"<<std::endl;
		return 1;
	}

	unsigned int nTasks = (int)*argv[2];
	pthread_t mythread[nTasks];	
	timespec start,end,time;

	nLoops = (int)* argv[1];
    
	//start timing
	clock_gettime(CLOCK_REALTIME,&start);
	//task work
	for(unsigned int i = 0;i<nTasks;i++){
		if ( pthread_create(&mythread[i], NULL, call_incr, NULL) ) {
		    printf("error creating thread.");
		    return 1;
		}
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
