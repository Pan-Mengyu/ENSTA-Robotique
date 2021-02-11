#include <iostream>
#include <time.h>
#include <sstream>

void incr(unsigned int nLoops, double* pCounter){
 	for(unsigned int i=0;i<nLoops;i++){
 		*pCounter += 1.0;
 	}
}

int main(int argc, char* argv[]){

	if(argc < 2){
		std::cerr<<"Usage:please add parameter"<<std::endl;
		return 1;
	}

	int nLoops = (int)*argv[1];
	double pCounter = 0.0;
	timespec start,end,time;

	//start timing
	clock_gettime(CLOCK_REALTIME,&start);
	incr(nLoops,&pCounter);
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
