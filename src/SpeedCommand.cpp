/*
 * SpeedCommand.cpp
 *
 *  Created on: 04.10.2016
 *      Author: imolcean
 */

#include "SpeedCommand.h"

#include "easylogging++.h"

namespace marco {

SpeedCommand::SpeedCommand(Robot& robot) : m_robot(robot) {}

void SpeedCommand::execute(std::vector<std::string> args)
{
	if(args.size() < 2)
	{
		LOG(ERROR) << "SpeedCommand: Not enough arguments. Command will be ignored." << std::endl;

		return;
	}

	std::string modifier;
	double val = 0;

	try
	{
		modifier = args.at(0);
		val = std::stod(args.at(1));
	}
	catch(std::invalid_argument& e)
	{
		LOG(ERROR) << "SpeedCommand: Invalid argument. " << e.what() << std::endl;

		return;
	}

	if(modifier == "set")
	{
		m_robot.setSpeed(val);
	}
	else if(modifier == "mod")
	{
		m_robot.changeSpeed(val);
	}
	else
	{
		LOG(WARNING) << "Invalid argument: " << modifier << std::endl;
	}
}

} /* namespace marco */
