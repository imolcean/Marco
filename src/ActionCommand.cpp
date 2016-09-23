/*
 * ActionCommand.cpp
 *
 *  Created on: 23.09.2016
 *      Author: imolcean
 */

#include "ActionCommand.h"

namespace marco
{

ActionCommand::ActionCommand(Robot& robot) : m_robot(robot) {}

void ActionCommand::execute(std::vector<std::string> args)
{
	// TODO Parse args and pass the command to the module
}

} /* namespace marco */
