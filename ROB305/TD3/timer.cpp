//#include "timespec.hpp"
#include "timer.h"
#include <time.h>
#include <unistd.h>
#include <cstdio>

Timer::Timer(){
	
}

Timer::~Timer(){
	
}

void Timer::start(double duration_ms){
	for(double i; i<duration_ms;i++){
		sleep(1);
		counter+=1;
		working = true;
		if(stopFlag){
			working = false;
			break;
		}
	}
	working = false;	
}

void Timer::stop(){
	while(working){
		stopFlag = true;
	}
	stopFlag = false;
	printf("counter is %f",counter);
}

void Timer::callback(){
	start(duration);
}

void PeriodicTimer::call_callback(){
	callback();
}

void PeriodicTimer::start(double duration_ms){
	for(double i; i<duration_ms;i++){
			sleep(1);
			counter+=1;
			working = true;
			if(stopFlag){
				working = false;
				break;
			}
		}
	working = false;
} 
