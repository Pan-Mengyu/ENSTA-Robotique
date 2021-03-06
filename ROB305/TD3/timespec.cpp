#include <iostream>
#include <time.h>
#include "timespec.hpp"

timespec timespec_from_ms(double time_ms){
	timespec time;
	time.tv_sec = int(time_ms)/1000;
	time.tv_nsec = (time_ms*1000*1000-int(time_ms)*1000*1000);
	return time;
}

double timespec_to_ms(const timespec& time_ts){
	double time;
	time = time_ts.tv_sec*1000+double(time_ts.tv_nsec)/1000/1000;
	return time;	
}

timespec timespec_now(){
	timespec time_now;
	clock_gettime(CLOCK_REALTIME, &time_now);
	return time_now;
}

timespec timespec_negate(const timespec& time_ts){
	timespec time;
	time.tv_sec = -time_ts.tv_sec;
	time.tv_nsec = - time_ts.tv_nsec;
	return time;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts){
	timespec time;
	time.tv_sec = time1_ts.tv_sec+time2_ts.tv_sec;
	time.tv_nsec = time1_ts.tv_nsec+time2_ts.tv_nsec;
	return time;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts){
	timespec time;
	time.tv_sec = time1_ts.tv_sec-time2_ts.tv_sec;
	time.tv_nsec = time1_ts.tv_nsec-time2_ts.tv_nsec;
	return time;
}

timespec timespec_wait(const timespec& delay_ts){
	nanosleep(&delay_ts,NULL);
	return delay_ts;
}

timespec Operator_reload::operator-(const timespec& time_ts){
	timespec time;
	time.tv_sec = -time_ts.tv_sec;
	time.tv_nsec = - time_ts.tv_nsec;
	return time;
}
timespec Operator_reload::operator+(const timespec& time1_ts,const timespec& time2_ts){
	timespec time;
	time.tv_sec = time1_ts.tv_sec+time2_ts.tv_sec;
	time.tv_nsec = time1_ts.tv_nsec+time2_ts.tv_nsec;
	return time;
}
timespec Operator_reload::operator-(const timespec& time1_ts,const timespec& time2_ts){
	timespec time;
	time.tv_sec = time1_ts.tv_sec-time2_ts.tv_sec;
	time.tv_nsec = time1_ts.tv_nsec-time2_ts.tv_nsec;
	return time;
}
timespec Operator_reload::operator+=(const timespec& time_ts,const timespec& delay_ts){
	timespec time;
	time.tv_sec = time_ts.tv_sec+delay_ts.tv_sec;
	time.tv_nsec = time_ts.tv_nsec+delay_ts.tv_nsec;
	return time;
}
timespec Operator_reload::operator-=(const timespec& time_ts,const timespec& delay_ts){
	timespec time;
	time.tv_sec = time_ts.tv_sec-delay_ts.tv_sec;
	time.tv_nsec = time_ts.tv_nsec-delay_ts.tv_nsec;
	return time;
}
bool Operator_reload::operator==(const timespec& time1_ts,const timespec& time2_ts){
	bool flag = false;
	if (time1_ts.tv_sec==time2_ts.tv_sec)&&(time1_ts.tv_nsec==time2_ts.tv_nsec){
		flag = true;
	}
	return flag;
}
bool Operator_reload::operator!=(const timespec& time1_ts,const timespec& time2_ts){
	bool flag = true;
	if (time1_ts.tv_sec==time2_ts.tv_sec)&&(time1_ts.tv_nsec==time2_ts.tv_nsec){
		flag = false;
	}
	return flag;
}
bool Operator_reload::operator<(const timespec& time1_ts,const timespec& time2_ts){
	bool flag = true;
	if(time1_ts.tv_sec>time2_ts.tv_sec){
		flag = false;
	}
	else if (time1_ts.tv_sec==time2_ts.tv_sec){
		if(time1_ts.tv_nsec>=time2_ts.tv_nsec){
			flag = false;
		}
	}
	else{
		flag = true;
	}
	return flag;
}
bool Operator_reload::operator>(const timespec& time1_ts,const timespec& time2_ts){
	bool flag = true;
	if(time1_ts.tv_sec<time2_ts.tv_sec){
		flag = false;
	}
	else if (time1_ts.tv_sec==time2_ts.tv_sec){
		if(time1_ts.tv_nsec<=time2_ts.tv_nsec){
			flag = false;
		}
	}
	else{
		flag = true;
	}
	return flag;
}