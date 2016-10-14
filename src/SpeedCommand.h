/*
 * SpeedCommand.h
 *
 *  Created on: 04.10.2016
 *      Author: imolcean
 */

#ifndef SRC_SPEEDCOMMAND_H_
#define SRC_SPEEDCOMMAND_H_

#include "Command.h"
#include "Robot.h"

namespace marco
{

/**
 * This command changes the speed of the robot.
 */
class SpeedCommand: public Command
{
private:
	Robot& m_robot;

public:

	/**
	 * Constructor.
	 *
	 * @param robot reference to the robot.
	 */
	SpeedCommand(Robot& robot);

	/**
	 * Executes the command.
	 *
	 * @param args parameters of the command
	 */
	virtual void execute(std::vector<std::string> args);
};

} /* namespace marco */

#endif /* SRC_SPEEDCOMMAND_H_ */
