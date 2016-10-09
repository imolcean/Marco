/*
 * Robot.cpp
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#include "Robot.h"
#include <iostream>
#include <math.h>

#include "easylogging++.h"

namespace marco
{

Robot::Robot(Track& leftTrack, Track& rightTrack, boost::asio::io_service& io) :
		m_leftTrack(leftTrack),
		m_rightTrack(rightTrack),
		m_timer(io, boost::bind(&Robot::timeout, this, boost::asio::placeholders::error)),
		m_speed(1) {}

Track& Robot::getLeftTrack()
{
	return m_leftTrack;
}

Track& Robot::getRightTrack()
{
	return m_rightTrack;
}

void Robot::move(double x, double y, int time)
{
	// Velocity of the tracks
	double vLeft;
	double vRight;

	// Dead zone close to zero
	if(fabs(x) < 0.1)
	{
		x = 0;
	}

	if(fabs(y) < 0.1)
	{
		y = 0;
	}

	// Normal speed is the length of the vector
	// Turn speed is the speed of the inner track
	double vNorm = sqrt(pow(x, 2) + pow(y, 2));
	double vTurn = vNorm - fabs(y);

	// Moving backwards
	if(x < 0)
	{
		vNorm = -vNorm;
		vTurn = -vTurn;
	}

	// Turning around
	//
	// When x is zero and y is not
	// robot will turn around it's center
	// and not around the track
	//
	// TODO Make configurable
	{
		if(x == 0)
		{
			if(y != 0)
			{
				vTurn = -vNorm;
			}
		}
	}


	// Determine direction of the turn
	if(y < 0)
	{
		vLeft = vNorm;
		vRight = vTurn;
	}
	else
	{
		vLeft = vTurn;
		vRight = vNorm;
	}

	// Normalize the values
	//
	// If values are bigger than 1.0
	// they will be scaled so the
	// biggest one will be 1.0
	//
	// TODO Make configurable
	{
		double t = std::max(fabs(vLeft), fabs(vRight));

		if(t > 1)
		{
			vLeft = vLeft / t;
			vRight = vRight / t;
		}
	}

	// Multiplying the speed with the speed coefficient of the robot
	vLeft = vLeft * m_speed;
	vRight = vRight * m_speed;

	m_leftTrack.move(vLeft);
	m_rightTrack.move(vRight);

	if(time > 0 && (x != 0 || y != 0))
	{
		m_timer.start(boost::posix_time::milliseconds(time));
	}
	else
	{
		m_timer.stop();
	}

	LOG(DEBUG) << "Control vector: " << x << ", " << y << ", " << time << ". Calculated values: " << vLeft << ", " << vRight << ", " << time << std::endl;
}

void Robot::stop()
{
	move(0, 0);
}

void Robot::timeout(const boost::system::error_code& e)
{
	if(e != boost::asio::error::operation_aborted)
	{
		stop();
	}
}

void Robot::setSpeed(double val)
{
	if(val > 1)
	{
		m_speed = 1;
	}
	else if(val < 0)
	{
		m_speed = 0;
	}
	else
	{
		m_speed = val;
	}

	LOG(DEBUG) << "Speed set to " << m_speed << std::endl;
}

void Robot::changeSpeed(double val)
{
	setSpeed(m_speed + val);
}

} /* namespace marco */
