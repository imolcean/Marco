/*
 * MoveCommand.cpp
 *
 *  Created on: 23.09.2016
 *      Author: imolcean
 */

#include "MoveCommand.h"
#include <iostream>

#include "easylogging++.h"

namespace marco
{

MoveCommand::MoveCommand(Robot& robot) : m_robot(robot) {}

void MoveCommand::execute(std::vector<std::string> args)
{
	if(args.size() < 2)
	{
		LOG(ERROR) << "MoveCommand: Not enough arguments. Command will be ignored." << std::endl;

		return;
	}

	double x = 0;
	double y = 0;
	int time = 0;

	try
	{
		x = std::stod(args.at(0));
		y = std::stod(args.at(1));

		if(args.size() >= 3)
		{
			time = std::stoi(args.at(2));
		}
	}
	catch(std::invalid_argument& e)
	{
		LOG(ERROR) << "MoveCommand: Invalid argument. " << e.what() << std::endl;

		return;
	}

	m_robot.move(x, y, time);
}

} /* namespace marco */
