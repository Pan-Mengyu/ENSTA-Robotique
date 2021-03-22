#ifndef timer_h_INCLUDED
#define timer_h_INCLUDED

#include <time.h>

class Timer{
	public:
		double counter;
		void Timer();
		void ~Timer();
		void start(double duration_ms);
		void stop();

	private:
		void callback()
};

class PeriodcTimer: public Timer
{
	public:
		void start(double duration_ms);
		
	private:
		void call_callback();
};


#endif
