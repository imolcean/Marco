/*
 * StreamListener.h
 *
 *  Created on: 07.10.2016
 *      Author: imolcean
 */

#ifndef SRC_STREAMLISTENER_H_
#define SRC_STREAMLISTENER_H_

#include <functional>

typedef std::function<void(std::string)> func;

namespace marco
{

class StreamListener
{
private:
	std::istream& m_stream;
	func m_callback;

public:
	StreamListener(std::istream& stream, func callback);

	void run();
};

} /* namespace marco */

#endif /* SRC_STREAMLISTENER_H_ */
