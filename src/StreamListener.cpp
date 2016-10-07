/*
 * StreamListener.cpp
 *
 *  Created on: 07.10.2016
 *      Author: imolcean
 */

#include "StreamListener.h"
#include <iostream>

namespace marco {

StreamListener::StreamListener(std::istream& stream, func callback) : m_stream(stream), m_callback(callback) {}

void StreamListener::run()
{
	std::string input;

	while(true)
	{
		std::getline(m_stream, input);

		m_callback(input);
	}
}

} /* namespace marco */
