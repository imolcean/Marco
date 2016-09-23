/*
 * Robot.cpp
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#include "Robot.h"
#include <iostream>

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
	// TODO LMY Algorithm
	std::cout << "ROBOT MOVE: " << x << ", " << y << ", " << time << std::endl;
}

void Robot::stop()
{
	move(0, 0);
}

} /* namespace marco */
