/*
 * Timer.h
 *
 *  Created on: 02.10.2016
 *      Author: imolcean
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace marco
{

/**
 * Provides interface for the asynchronous timer with callback.
 */
class Timer
{
	typedef boost::asio::io_service IOService;
	typedef boost::asio::deadline_timer DTimer;
	typedef DTimer::duration_type Duration;
	typedef boost::function<void (boost::system::error_code)> Func;

private:
	DTimer m_timer;
	Func m_callback;

public:

	/**
	 * Constructor.
	 *
	 * @param io io service
	 * @param callback timeout callback function
	 */
	Timer(IOService& io, Func callback);

	/**
	 * Starts the timer or restarts it with the
	 * new deadline if it was already running.
	 *
	 * @param interval deadline
	 */
	void start(Duration interval);

	/**
	 * Stops the timer.
	 */
	void stop();

	/**
	 * Destructor.
	 */
	~Timer();
};

} /* namespace marco */

#endif /* SRC_TIMER_H_ */
