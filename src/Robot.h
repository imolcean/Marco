/*
 * Robot.h
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Config.h"
#include "Track.h"

namespace marco
{

class Robot
{
private:
	Config& m_config;
	Track& m_leftTrack;
	Track& m_rightTrack;

public:
	Robot(Config& config, Track& leftTrack, Track& rightTrack);
	Track& getLeftTrack();
	Track& getRightTrack();
	Config& getConfig();
};

} /* namespace marco */

#endif /* ROBOT_H_ */
