#include <time.h>
#include <cerrno>
#include "timespec.hpp"


double timespec_to_ms(const timespec& time_ts)
{
	double time_ms = 0.0;
	time_ms = time_ts.tv_sec*1000 + time_ts.tv_nsec/1e6;
	return time_ms;
}

timespec timespec_from_ms(double time_ms)
{
	struct timespec time_ts;
	time_ts.tv_sec = time_ms/1e3;
	if (time_ms < 0){
		time_ts.tv_sec -= 1;
	}
	time_ts.tv_nsec = (time_ms - time_ts.tv_sec*1e3)*1e6;
	return time_ts;
}

timespec timespec_now()
{
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now;
}

timespec timespec_negate(const timespec& time_ts)
{
	struct timespec time_neg;
	if (time_ts.tv_nsec == 0){
		time_neg.tv_sec = -time_ts.tv_sec;
		time_neg.tv_nsec = 0;
	}
	else{
		time_neg.tv_sec = -time_ts.tv_sec - 1;
		time_neg.tv_nsec = 1e9 - time_ts.tv_nsec;
	}
	return time_neg;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
	struct timespec time_sum;                                       
    time_sum.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
    time_sum.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    if(time_sum.tv_nsec >= 1e9){
        time_sum.tv_sec += 1;
        time_sum.tv_nsec -= 1e9;
    }
    return time_sum;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
    struct timespec time_sub;
    time_sub.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
    if(time1_ts.tv_nsec - time2_ts.tv_nsec < 0)
    {
        time_sub.tv_sec -= 1;
        time_sub.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec + 1e9;
    }
    else {time_sub.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;}
    return time_sub;
}

timespec timespec_wait(const timespec& delay_ts)
{
	struct timespec rem_ts;
	if (nanosleep(&delay_ts, &rem_ts) == -1){
		if (errno == EINTR){
			timespec_wait(rem_ts);
		}
	}
	return rem_ts;
}

timespec  operator- (const timespec& time_ts)
{
	return timespec_negate(time_ts);
}

timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts)
{
	return timespec_add(time1_ts, time2_ts);
}

timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)
{
	return timespec_subtract(time1_ts, time2_ts);
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts)
{
	time_ts = timespec_add(time_ts, delay_ts);
	return time_ts;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts)
{
	time_ts = timespec_subtract(time_ts, delay_ts);
	return time_ts;
}

bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
	return (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec == time2_ts.tv_nsec);
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
	return (time1_ts.tv_sec != time2_ts.tv_sec || time1_ts.tv_nsec != time2_ts.tv_nsec);
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts)
{
	return (time1_ts.tv_sec < time2_ts.tv_sec || (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec < time2_ts.tv_nsec));
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts)
{
	return (time1_ts.tv_sec > time2_ts.tv_sec || (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec > time2_ts.tv_nsec));
}
