#include <iostream>
#include <time.h>

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

int main(){
	timespec ts;
	ts.tv_sec = 2;
	ts.tv_nsec = 1;
	const timespec& time_ts = ts;
	double tms;

	tms = timespec_to_ms(time_ts);
	printf("time to ms:%ld,%ld -> %lf\n",time_ts.tv_sec,time_ts.tv_nsec,tms);
	ts = timespec_from_ms(tms);
	printf("time from ms:%lf -> %ld,%ld\n",tms,ts.tv_sec,ts.tv_nsec);
	
}
