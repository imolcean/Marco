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
#include <mutex>
#include "ControlEntity.h"

namespace marco
{

class InputHandler
{
private:
	ControlEntity& m_buffer;
	bool& m_flag;
	std::mutex& m_lock;
	std::istream& m_stream;

	bool m_running;

public:
	/**
	 * Main constructor.
	 *
	 * @param buffer buffer control entity where the received commands are stored
	 * @param flag is set when a new command has been received
	 * @param lock mutex to synchronize access to the buffer
	 * @param src input stream the handler will listen to
	 */
	InputHandler(ControlEntity& buffer, bool& flag, std::mutex& lock, std::istream& src = std::cin);

	/**
	 * Starts the input handler in a separate thread.
	 *
	 * Can only be called once. If the handler is already started
	 * the further calls will be ignored.
	 */
	void run();

	/**
	 * Listens for the input from the given stream.
	 */
	void listen();

	/**
	 * Parses the input.
	 *
	 * @param str input string
	 * @param cvector control entity which stores the values parsed from the input string
	 * @return true if input string is valid and has been parsed,
	 * false otherwise
	 */
	bool parse(std::string str, ControlEntity& cvector);
};

} /* namespace marco */

#endif /* SRC_INPUTHANDLER_H_ */
