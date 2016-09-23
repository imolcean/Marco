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

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(std::vector<std::string> args) = 0;
};

} /* namespace marco */

#endif /* SRC_COMMAND_H_ */
