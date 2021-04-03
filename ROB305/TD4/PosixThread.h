#include <pthread.h>
#include <exception>
#include <string>
#include <signal.h>
#include <iostream> 
#include "chrono.h"
using namespace std; 

class PosixThread{
	private:
		pthread_t posixId;
		pthread_attr_t posixAttr;
	protected:
		bool isActive = false;
	public:
		class Exception;
		PosixThread();
		~PosixThread();
		PosixThread(pthread_t posixId);
		void start(void*(* threadFunc)(void*), void* threadArg);
		void join();
		bool join(double timeout_ms);
		bool setScheduling(int schedPolicy,int priority);
		bool getScheduling(int* schedPolicy,int* priority);	
};

class PosixThread::Exception : public exception{
	public:
		Exception(const string& msg);
		const char* what() const throw(){ 
       		return error_message.c_str();     
		}
	private:
		string error_message;
};


class Thread : public PosixThread{	
	private:
		Chrono chrono;
		bool isStarted = false;

	public:
		Thread();
		~Thread();
		void start();
		void sleep_ms(double delay_ms);
		double startTime_ms();
		double stopTime_ms();
		double execTime_ms();

		//only for the test
		int nLoops = 0;
		double pCounter = 0.0;
		
	protected:
		void run();
		
	private :
		static void* call_run(void* v_thread);
};
