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

/**
 * Parses and handles the input command.
 */
class InputHandler
{
private:
	Command* m_move;
	Command* m_stop;
	Command* m_action;
	Command* m_speed;

	/**
	 * Parses the input into a vector of tokens.
	 *
	 * @param input input string
	 */
	std::vector<std::string> parse(std::string input);

public:
	/**
	 * Main constructor.
	 *
	 * @param robot reference to the robot.
	 */
	InputHandler(Robot& robot);

	/**
	 * Handles the input.
	 *
	 * @param input input string
	 */
	void handle(std::string input);

	/**
	 * Destructor.
	 */
	~InputHandler();
};

} /* namespace marco */

#endif /* SRC_INPUTHANDLER_H_ */
