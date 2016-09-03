/*
 * Robot.cpp
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#include "Robot.h"

namespace marco
{

Robot::Robot(Config& config, Track& leftTrack, Track& rightTrack) :
		m_config(config), m_leftTrack(leftTrack), m_rightTrack(rightTrack) {}

Track& Robot::getLeftTrack()
{
	return m_leftTrack;
}

Track& Robot::getRightTrack()
{
	return m_rightTrack;
}

Config& Robot::getConfig()
{
	return m_config;
}

} /* namespace marco */
