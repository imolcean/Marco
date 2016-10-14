/*
 * ActionCommand.h
 *
 *  Created on: 23.09.2016
 *      Author: imolcean
 */

#ifndef SRC_ACTIONCOMMAND_H_
#define SRC_ACTIONCOMMAND_H_

#include "Command.h"
#include "Robot.h"

namespace marco
{

/**
 * This command calls the given command of a robot module.
 */
class ActionCommand: public Command
{
private:
	Robot& m_robot;

public:

	/**
	 * Constructor.
	 *
	 * @param robot reference to the robot
	 */
	ActionCommand(Robot& robot);

	/**
	 * Executes the command.
	 *
	 * @param args parameters of the command
	 */
	virtual void execute(std::vector<std::string> args);
};

} /* namespace marco */

#endif /* SRC_ACTIONCOMMAND_H_ */
