#ifndef timer_h_INCLUDED
#define timer_h_INCLUDED

#include <time.h>
#include <stdbool.h>


class Timer{
	public:
		Timer();
		~Timer();
		void start(double duration_ms);
		void stop();
		double counter;
		bool stopFlag = false;
		bool working = false;
		double duration;

	protected:
		void callback();
};

class PeriodicTimer: public Timer
{
	public:
		void start(double duration_ms);
		
	private:
		void call_callback();
};


#endif
