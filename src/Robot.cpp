/*
 * Robot.cpp
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#include "Robot.h"

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

} /* namespace marco */
