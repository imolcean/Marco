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
	Timer(IOService& io, Func callback);
	void start(Duration interval);
	void stop();
	~Timer();
};

} /* namespace marco */

#endif /* SRC_TIMER_H_ */
