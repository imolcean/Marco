/*
 * Robot.h
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Track.h"

namespace marco
{

class Robot
{
private:
	Track& m_leftTrack;
	Track& m_rightTrack;

public:
	Robot(Track& leftTrack, Track& rightTrack);
	Track& getLeftTrack();
	Track& getRightTrack();
	void move(double x, double y, int time = 0);
	void stop();
};

} /* namespace marco */

#endif /* ROBOT_H_ */
