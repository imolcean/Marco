/*
 * InputHandler.cpp
 *
 *  Created on: 19.09.2016
 *      Author: imolcean
 */

#include "InputHandler.h"
#include <boost/algorithm/string.hpp>

#include "easylogging++.h"

namespace marco {

InputHandler::InputHandler(Robot& robot) :
		m_move(new MoveCommand(robot)),
		m_stop(new StopCommand(robot)),
		m_action(new ActionCommand(robot)),
		m_speed(new SpeedCommand(robot)) {}

std::vector<std::string> InputHandler::parse(std::string input)
{
	std::vector<std::string> tokens;

	boost::to_lower(input);
	boost::trim(input);
	boost::split(tokens, input, boost::is_any_of(" "), boost::token_compress_on);

	return tokens;
}

void InputHandler::handle(std::string input)
{
	std::vector<std::string> tokens = parse(input);

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
	delete m_speed;
}

} /* namespace marco */
