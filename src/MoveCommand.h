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

class MoveCommand: public Command
{
private:
	Robot& m_robot;

public:
	MoveCommand(Robot& robot);
	virtual void execute(std::vector<std::string> args);
};

} /* namespace marco */

#endif /* SRC_MOVECOMMAND_H_ */
