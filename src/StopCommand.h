/*
 * StopCommand.h
 *
 *  Created on: 23.09.2016
 *      Author: imolcean
 */

#ifndef SRC_STOPCOMMAND_H_
#define SRC_STOPCOMMAND_H_

#include "Command.h"
#include "Robot.h"

namespace marco
{

/**
 * This command stops the robot if it was moving.
 */
class StopCommand: public Command
{
private:
	Robot& m_robot;

public:

	/**
	 * Constructor.
	 *
	 * @param robot reference to the robot.
	 */
	StopCommand(Robot& robot);

	/**
	 * Executes the command.
	 *
	 * @param args parameters of the command
	 */
	virtual void execute(std::vector<std::string> args);
};

} /* namespace marco */

#endif /* SRC_STOPCOMMAND_H_ */
