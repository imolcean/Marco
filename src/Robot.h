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

class Robot
{
private:
	Track& m_leftTrack;
	Track& m_rightTrack;
	Timer m_timer;

public:
	Robot(Track& leftTrack, Track& rightTrack, boost::asio::io_service& io);
	Track& getLeftTrack();
	Track& getRightTrack();
	void move(double x, double y, int time = 0);
	void stop();
	void timeout(const boost::system::error_code& e);
};

} /* namespace marco */

#endif /* ROBOT_H_ */
