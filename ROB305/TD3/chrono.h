#ifndef chrono_h_INCLUDED
#define chrono_h_INCLUDED

#include <time.h>

class Chrono{
private:
	timespec m_startTime;
	timespec m_stopTime;

public:
	double startTime() const;
	double stopTime() const;
	void restart();
	void stop();
	bool isactive();
	double lap() const;
};

#endif
