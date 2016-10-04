/*
 * InputHandler.cpp
 *
 *  Created on: 19.09.2016
 *      Author: imolcean
 */

#include "InputHandler.h"
#include <boost/algorithm/string.hpp>
#include <iostream>

#include "easylogging++.h"

namespace marco {

InputHandler::InputHandler(Robot& robot, std::istream& stream) :
		m_stream(stream),
		m_running(false),
		m_move(new MoveCommand(robot)),
		m_stop(new StopCommand(robot)),
		m_action(new ActionCommand(robot)),
		m_speed(new SpeedCommand(robot)) {}

void InputHandler::run()
{
	if(!m_running)
	{
		m_running = true;
		std::thread t(&InputHandler::listen, this);
		t.detach();

		// TODO Thread control, not just detach
	}
}

void InputHandler::listen()
{
	std::string input;

	while(true)
	{
		std::getline(m_stream, input);

		std::vector<std::string> tokens = parse(input);

		handle(tokens);
	}
}

std::vector<std::string> InputHandler::parse(std::string str)
{
	std::vector<std::string> tokens;

	boost::to_lower(str);
	boost::trim(str);
	boost::split(tokens, str, boost::is_any_of(" "), boost::token_compress_on);

	return tokens;
}

void InputHandler::handle(std::vector<std::string> tokens)
{
	if(tokens.empty())
	{
		return;
	}

	std::string cmd = *tokens.begin();

	tokens.erase(tokens.begin());

	if(cmd == "action")
	{
		m_action->execute(tokens);
	}
	else if(cmd == "move")
	{
		m_move->execute(tokens);
	}
	else if(cmd == "stop")
	{
		m_stop->execute(tokens);
	}
	else if(cmd == "speed")
	{
		m_speed->execute(tokens);
	}
	else
	{
		LOG(WARNING) << "Invalid command: " << cmd << std::endl;
	}
}

InputHandler::~InputHandler()
{
	delete m_action;
	delete m_move;
	delete m_stop;
}

} /* namespace marco */
