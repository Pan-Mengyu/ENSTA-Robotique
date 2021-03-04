#include "chrono.h"
#include "timespec.h"
#include <time.h>

Chrono::Chrono(){
	restart();
}

double Chrono::startTime() const{
	return timespec_to_ms(m_startTime);
}

double Chrono::stopTime() const{
	return timespec_to_ms(m_stopTime);
}

void Chrono::restart() {
	m_startTime = timspec_now();
}

void Chrono::stop() {
	m_stopTime = timspec_now();
}

bool Chrono::isactive() {
	return m_startTime == m_stopTime;
}

double Chrono::lap() const{
	timespec duration = m_startTime;
	if (isactive()){
		duration = timespec_now()-m_startTime;
	}
	else{
		duration = m_stopTime-m_startTime;
	}
	return duration;
}
