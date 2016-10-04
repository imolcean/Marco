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

class SpeedCommand: public Command
{
private:
	Robot& m_robot;

public:
	SpeedCommand(Robot& robot);
	virtual void execute(std::vector<std::string> args);
};

} /* namespace marco */

#endif /* SRC_SPEEDCOMMAND_H_ */
