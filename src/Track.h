/*
 * Track.h
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#ifndef TRACK_H_
#define TRACK_H_

#include <array>

namespace marco
{

class Track
{
private:
	std::array<int, 3> pins;
	double m_velocity;
	bool m_direction;

public:
	Track(int pinA, int pinB, int pinE);

	int getPinA();
	int getPinB();
	int getPinE();

	double getVelocity();
	void setVelocity(double value);

	bool getDirection();
	void setDirection(bool value);

	void act();
};

} /* namespace marco */

#endif /* TRACK_H_ */
