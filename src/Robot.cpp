/*
 * Robot.cpp
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#include "Robot.h"
#include <iostream>
#include <math.h>

namespace marco
{

Robot::Robot(Track& leftTrack, Track& rightTrack) :
		m_leftTrack(leftTrack), m_rightTrack(rightTrack) {}

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
	// TODO Timer

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

	m_leftTrack.setVelocity(vLeft);
	m_rightTrack.setVelocity(vRight);

	std::cout << "ROBOT MOVE: " << vLeft << ", " << vRight << ", " << time << std::endl;
}

void Robot::stop()
{
	move(0, 0);
}

} /* namespace marco */
