/*
 * MoveCommand.h
 *
 *  Created on: 23.09.2016
 *      Author: imolcean
 */

#ifndef SRC_MOVECOMMAND_H_
#define SRC_MOVECOMMAND_H_

#include "Command.h"
#include "Robot.h"

namespace marco
{

/**
 * This command moves the robot in the given
 * direction with the given timeout.
 */
class MoveCommand: public Command
{
private:
	Robot& m_robot;

public:

	/**
	 * Constructor.
	 *
	 * @param robot reference to the robot.
	 */
	MoveCommand(Robot& robot);

	/**
	 * Executes the command.
	 *
	 * @param args parameters of the command
	 */
	virtual void execute(std::vector<std::string> args);
};

} /* namespace marco */

#endif /* SRC_MOVECOMMAND_H_ */
