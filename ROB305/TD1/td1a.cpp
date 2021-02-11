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

class Operator_reload{
	public:
		timespec t1, t2;
		timespec operator-(const timespec& time_ts){
			timespec time;
			time.tv_sec = -time_ts.tv_sec;
			time.tv_nsec = - time_ts.tv_nsec;
			return time;
		}
		timespec operator+(const timespec& time1_ts,const timespec& time2_ts){
			timespec time;
			time.tv_sec = time1_ts.tv_sec+time2_ts.tv_sec;
			time.tv_nsec = time1_ts.tv_nsec+time2_ts.tv_nsec;
			return time;
		}
		timespec operator-(const timespec& time1_ts,const timespec& time2_ts){
			timespec time;
			time.tv_sec = time1_ts.tv_sec-time2_ts.tv_sec;
			time.tv_nsec = time1_ts.tv_nsec-time2_ts.tv_nsec;
			return time;
		}
		timespec operator+=(const timespec& time_ts,const timespec& delay_ts){
			timespec time;
			time.tv_sec = time_ts.tv_sec+delay_ts.tv_sec;
			time.tv_nsec = time_ts.tv_nsec+delay_ts.tv_nsec;
			return time;
		}
		timespec operator-=(const timespec& time_ts,const timespec& delay_ts){
			timespec time;
			time.tv_sec = time_ts.tv_sec-delay_ts.tv_sec;
			time.tv_nsec = time_ts.tv_nsec-delay_ts.tv_nsec;
			return time;
		}
		bool operator==(const timespec& time1_ts,const timespec& time2_ts){
			bool flag = false;
			if (time1_ts.tv_sec==time2_ts.tv_sec)&&(time1_ts.tv_nsec==time2_ts.tv_nsec){
				flag = true;
			}
			return flag;
		}
		bool operator!=(const timespec& time1_ts,const timespec& time2_ts){
			bool flag = true;
			if (time1_ts.tv_sec==time2_ts.tv_sec)&&(time1_ts.tv_nsec==time2_ts.tv_nsec){
				flag = false;
			}
			return flag;
		}
		bool operator<(const timespec& time1_ts,const timespec& time2_ts){
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
		bool operator>(const timespec& time1_ts,const timespec& time2_ts){
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
};

int main(){
	timespec ts,time_now,t1,t2;
	ts.tv_sec = 2;
	ts.tv_nsec = 1;
	t1.tv_sec = 5;
	t1.tv_nsec = 3;
	t2.tv_sec = 2;
	t2.tv_nsec = 2;
	const timespec& time_ts = ts;
	double tms;

	tms = timespec_to_ms(time_ts);
	printf("time to ms:%ld,%ld -> %lf\n",time_ts.tv_sec,time_ts.tv_nsec,tms);
	ts = timespec_from_ms(tms);
	printf("time from ms:%lf -> %ld,%ld\n",tms,ts.tv_sec,ts.tv_nsec);
	time_now = timespec_now();
	printf("time for now:%ld,%ld\n",time_now.tv_sec,time_now.tv_nsec);
	ts =  timespec_negate(time_ts);
	printf("time negate:%ld,%ld\n",ts.tv_sec,ts.tv_nsec);
	ts = timespec_add(t1,t2);
	printf("time add:(%ld,%ld) + (%ld,%ld) = (%ld,%ld)\n",t1.tv_sec,t1.tv_nsec,t2.tv_sec,t2.tv_nsec,ts.tv_sec,ts.tv_nsec);
	ts = timespec_subtract(t1,t2);
	printf("time substract:(%ld,%ld) - (%ld,%ld) = (%ld,%ld)\n",t1.tv_sec,t1.tv_nsec,t2.tv_sec,t2.tv_nsec,ts.tv_sec,ts.tv_nsec);
	timespec_wait(time_ts);
	printf("time wait:%ld s, %ld ns \n",time_ts.tv_sec,time_ts.tv_nsec);
}
