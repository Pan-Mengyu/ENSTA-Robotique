#include <iostream>
#include <time.h>
#include <sstream>
#include <climits>

void callback(timespec start,timespec end,bool* pStop){
	if(end.tv_sec-start.tv_sec>4){
		*pStop = true;
	}
}

void incr(unsigned int nLoops, double* pCounter,bool* pStop){
	timespec start,end,time;
	//start timing
	clock_gettime(CLOCK_REALTIME,&start);
 	for(unsigned int i=0;(i<nLoops)&&(*pStop=false);i++){
 		*pCounter += 1.0;
 		//end timing
 		clock_gettime(CLOCK_REALTIME,&end);
 		
	}

	//calculate time
	if(end.tv_nsec<start.tv_nsec){
		time.tv_sec = end.tv_sec - 1 -start.tv_sec;
		time.tv_nsec = end.tv_nsec + 1000000000 - start.tv_nsec;
	}
	else{
		time.tv_sec = end.tv_sec  -start.tv_sec;
		time.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	
 	printf("Counter=%f\n",*pCounter);
 	printf("time is %ld s, %ld ns\n",time.tv_sec,time.tv_nsec);
}

int main(int argc, char* argv[]){

	int nLoops = UINT_MAX;
	double pCounter = 0.0;	
	bool pStop = false;

	incr(nLoops,&pCounter,&pStop);

	return 0;
}
