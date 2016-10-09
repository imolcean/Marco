/*
 * Track.h
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#ifndef TRACK_H_
#define TRACK_H_

#include <fstream>

namespace marco
{

class Track
{
private:
	unsigned int m_pinA;
	unsigned int m_pinB;
	unsigned int m_pinE;

	std::ofstream m_pwm;

	void setDirection(bool forward);
	void setVelocity(double value);

public:
	Track(unsigned int pinA, unsigned int pinB, unsigned int pinE);
	void move(double value);
	void stop();
	~Track();
};

} /* namespace marco */

#endif /* TRACK_H_ */
