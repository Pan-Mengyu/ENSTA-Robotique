#include <time.h>
#include <iostream>
#include <unistd.h>
#include "chrono.h"
#include <cstdlib>

int main(int argc, char* argv[]){
	unsigned int waitTime_s = 1;
	if (argc > 1){
		waitTime_s = std::atoi(argv[1]);
	}
	std::cout<<"Wait time for"<<waitTime_s<<"second"<<std::endl;
	sleep(waitTime_s);
	std::cout<<"finish waiting"<<std::endl;
	return 0;
}
