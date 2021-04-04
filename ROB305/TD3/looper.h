#ifndef looper_hpp_INCLUDED
#define looper_hpp_INCLUDED

#include "timer.h"
#include <cfloat>
#include <vector>

class Looper{
	protected:
		bool doStop;
		double iLoop;
	public:
		double runLoop(double nLoop);
		double getSample();
		double stopLoop();
};

class Calibrator: public PeriodicTimer{
	protected:
		double a;
		double b;
		std::vector<double> samples;
	public:
		Calibrator(double samplingPeriod_ms, unsigned nSamples);
		double nLoops(double duration_ms);
};


class CpuLoop: public Looper{
	public:
		CpuLoop(Calibrator& calibrator);
		void runTime(double duration_ms);
};

#endif
