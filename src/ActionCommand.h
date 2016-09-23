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

class ActionCommand: public Command
{
private:
	Robot& m_robot;


public:
	ActionCommand(Robot& robot);
	virtual void execute(std::vector<std::string> args);
};

} /* namespace marco */

#endif /* SRC_ACTIONCOMMAND_H_ */
