/*
 * Command.h
 *
 *  Created on: 23.09.2016
 *      Author: imolcean
 */

#ifndef SRC_COMMAND_H_
#define SRC_COMMAND_H_

#include <vector>
#include <string>

namespace marco
{

/**
 * Abstract class for the commands.
 * Every command has to implement execute() method.
 */
class Command
{
public:

	/**
	 * Destructor.
	 */
	virtual ~Command() {};

	/**
	 * This method executes the command with the given arguments.
	 *
	 * @param args parameters of the command
	 */
	virtual void execute(std::vector<std::string> args) = 0;
};

} /* namespace marco */

#endif /* SRC_COMMAND_H_ */
