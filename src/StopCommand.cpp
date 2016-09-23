/*
 * StopCommand.cpp
 *
 *  Created on: 23.09.2016
 *      Author: imolcean
 */

#include "StopCommand.h"

namespace marco
{

StopCommand::StopCommand(Robot& robot) : m_robot(robot) {}

void StopCommand::execute(std::vector<std::string> args)
{
	m_robot.stop();
}

} /* namespace marco */
