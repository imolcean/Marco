/*
 * Robot.h
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <boost/asio.hpp>
#include "Track.h"
#include "Timer.h"

namespace marco
{

/**
 * Provides interface to control the robot.
 */
class Robot
{
private:
	Track& m_leftTrack;
	Track& m_rightTrack;
	Timer m_timer;

	double m_minSpeed;
	double m_maxSpeed;
	double m_speed;

public:

	// TODO May be let the robot read the config file
	//		to reduce the amount of arguments in the constructor

	/**
	 * Constructor.
	 *
	 * @param leftTrack left track of the robot
	 * @param rightTrack right track of the robot
	 * @param io io service for the timer
	 */
	Robot(Track& leftTrack, Track& rightTrack, boost::asio::io_service& io, double minSpeed = 0, double maxSpeed = 1);

	/**
	 * Getter for the left track.
	 */
	Track& getLeftTrack();

	/**
	 * Getter for the right track.
	 */
	Track& getRightTrack();

	/**
	 * Getter for the min speed.
	 */
	double getMinSpeed();

	/**
	 * Getter for the max speed.
	 */
	double getMaxSpeed();

	/**
	 * Moves the robot in the given direction
	 * with the given timeout.
	 *
	 * @param x x component of the moving vector
	 * @param y y component of the moving vector
	 * @param time the robot will stop after this time (if no more commands received before)
	 */
	void move(double x, double y, int time = 0);

	/**
	 * Stops the robot if it was moving.
	 */
	void stop();

	/**
	 * Timeout callback.
	 *
	 * @param e error code of the timer
	 */
	void timeout(const boost::system::error_code& e);

	/**
	 * Sets the speed of the robot to the given value.
	 *
	 * @param val new speed
	 */
	void setSpeed(double val);

	/**
	 * Changes the speed of the robot on the given value.
	 *
	 * @param val speed delta
	 */
	void changeSpeed(double val);
};

} /* namespace marco */

#endif /* ROBOT_H_ */
