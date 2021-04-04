#include "looper.h"
#include <cstdio>

double Looper::runLoop(double nLoops){
	doStop = false;
	if(!doStop){
		while(iLoop<nLoops){
			iLoop++;
		}
	}
	return iLoop;
}

double Looper::getSample(){
	return iLoop;
}

double Looper::stopLoop(){
	doStop = true;
	return iLoop;
}

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples){
	Looper looper;
	looper.runLoop(DBL_MAX);
	double sample =  0;
	start(samplingPeriod_ms);
	
	double average_loops = 0;
	double average_time = 0;
	for (unsigned i = 0; i < nSamples; i++){
		average_loops += samples[i];
		average_time += samplingPeriod_ms*(i+1);
	}
	average_loops = average_loops/nSamples;
	average_time = average_time/nSamples;
	
	for (unsigned j = 1; j < nSamples; j++){
		sample += (samples[j] - samples[0])/(j*samplingPeriod_ms);
	}
	a = sample/(nSamples - 1);
	b = average_loops - a * average_time;

	looper.stopLoop();
}

double Calibrator::nLoops(double duration_ms){
	return a*duration_ms + b;
}

CpuLoop::CpuLoop(Calibrator& calibrator){

}

void CpuLoop::runTime(double duration_ms){
	//use parameter (samplingPeriod_ms, nSamples) = (1000,15) to test
	Calibrator calibrator(1000,15);
	runLoop(calibrator.nLoops(duration_ms));
}





