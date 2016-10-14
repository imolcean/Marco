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

/**
 * Listens to an input stream and calls a callback
 * function when receives a line.
 */
class StreamListener
{
private:
	std::istream& m_stream;
	func m_callback;

public:

	/**
	 * Constructor.
	 *
	 * @param stream input stream to listen to
	 * @param callback callback function to call when the line is read
	 */
	StreamListener(std::istream& stream, func callback);

	/**
	 * Starts the listening.
	 *
	 * This method blocks, so call it in a separate thread.
	 */
	void run();
};

} /* namespace marco */

#endif /* SRC_STREAMLISTENER_H_ */
