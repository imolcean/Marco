/*
 * Track.cpp
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#include "Track.h"

namespace marco {

Track::Track(int pinA, int pinB, int pinE) : m_velocity(0), m_direction(true)
{
	pins[0] = pinA;
	pins[1] = pinB;
	pins[2] = pinE;
}

int Track::getPinA()
{
	return pins[0];
}

int Track::getPinB()
{
	return pins[1];
}

int Track::getPinE()
{
	return pins[2];
}

double Track::getVelocity()
{
	return m_velocity;
}

void Track::setVelocity(double value)
{
	m_velocity = value;
}

bool Track::getDirection()
{
	return m_direction;
}

void Track::setDirection(bool value)
{
	m_direction = value;
}

void Track::act()
{
	// TODO
}

} /* namespace marco */
