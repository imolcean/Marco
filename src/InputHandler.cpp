/*
 * InputHandler.cpp
 *
 *  Created on: 19.09.2016
 *      Author: imolcean
 */

#include "InputHandler.h"

namespace marco {

InputHandler::InputHandler(ControlEntity& buffer, bool& flag, std::mutex& lock, std::istream& stream) :
		m_buffer(buffer), m_flag(flag), m_lock(lock), m_stream(stream), m_running(false) {}

void InputHandler::run()
{
	if(!m_running)
	{
		m_running = true;
		std::thread t(&InputHandler::listen, this);
	}
}

void InputHandler::listen()
{
	std::string input;
	ControlEntity tmp;

	while(true)
	{
		std::getline(m_stream, input);

		if(parse(input, tmp))
		{
			std::lock_guard<std::mutex> guard(lock);

			m_flag = true;
			m_buffer = tmp;
		}
	}
}

bool InputHandler::parse(std::string str, ControlEntity& cvector)
{
	bool success = false;

	// TODO Parsing

	if(success)
	{
		return true;
	}

	return false;
}

} /* namespace marco */
