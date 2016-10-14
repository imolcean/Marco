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

/**
 * Provides interface to control a track of the robot.
 */
class Track
{
private:
	unsigned int m_pinA;
	unsigned int m_pinB;
	unsigned int m_pinE;

	std::ofstream m_pwm;

	/**
	 * Sets the direction of the movement.
	 *
	 * @param forward whether the track has to move forward
	 */
	void setDirection(bool forward);

	/**
	 * Sets the speed of the track.
	 *
	 * @param value new speed of the track
	 */
	void setVelocity(double value);

public:

	/**
	 * Constructor.
	 *
	 * @param pinA input A of the motor driver
	 * @param pinB input B of the motor driver
	 * @param pinE Enable input of the motor driver
	 */
	Track(unsigned int pinA, unsigned int pinB, unsigned int pinE);

	/**
	 * Moves the track.
	 *
	 * @param value speed of the track, if negative then will move backwards
	 */
	void move(double value);

	/**
	 * Stops the track if it was moving.
	 */
	void stop();

	/**
	 * Destructor.
	 */
	~Track();
};

} /* namespace marco */

#endif /* TRACK_H_ */
