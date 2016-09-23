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

class StopCommand: public Command
{
private:
	Robot& m_robot;

public:
	StopCommand(Robot& robot);
	virtual void execute(std::vector<std::string> args);
};

} /* namespace marco */

#endif /* SRC_STOPCOMMAND_H_ */
