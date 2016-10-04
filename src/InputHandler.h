/*
 * InputHandler.h
 *
 *  Created on: 19.09.2016
 *      Author: imolcean
 */

#ifndef SRC_INPUTHANDLER_H_
#define SRC_INPUTHANDLER_H_

#include <iostream>
#include <thread>
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
	std::istream& m_stream;
	bool m_running;

	Command* m_move;
	Command* m_stop;
	Command* m_action;
	Command* m_speed;

	/**
	 * Listens for the input from the given stream.
	 */
	void listen();

	/**
	 * Parses the input.
	 */
	std::vector<std::string> parse(std::string str);

	/**
	 * Handles the input.
	 */
	void handle(std::vector<std::string> tokens);

public:
	/**
	 * Main constructor.
	 */
	InputHandler(Robot& robot, std::istream& src = std::cin);

	/**
	 * Starts the input handler in a separate thread.
	 *
	 * Can only be called once. If the handler is already started
	 * the further calls will be ignored.
	 */
	void run();

	/**
	 * Destructor.
	 */
	~InputHandler();
};

} /* namespace marco */

#endif /* SRC_INPUTHANDLER_H_ */
