/*
 * InputHandler.h
 *
 *  Created on: 19.09.2016
 *      Author: imolcean
 */

#ifndef SRC_INPUTHANDLER_H_
#define SRC_INPUTHANDLER_H_

#include "Command.h"
#include "ActionCommand.h"
#include "MoveCommand.h"
#include "StopCommand.h"
#include "SpeedCommand.h"
#include "Robot.h"

namespace marco
{

class InputHandler
{
private:
	Command* m_move;
	Command* m_stop;
	Command* m_action;
	Command* m_speed;

	/**
	 * Parses the input.
	 */
	std::vector<std::string> parse(std::string input);

public:
	/**
	 * Main constructor.
	 */
	InputHandler(Robot& robot);

	/**
	 * Handles the input.
	 */
	void handle(std::string input);

	/**
	 * Destructor.
	 */
	~InputHandler();
};

} /* namespace marco */

#endif /* SRC_INPUTHANDLER_H_ */
