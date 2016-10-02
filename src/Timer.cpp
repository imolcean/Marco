/*
 * Timer.cpp
 *
 *  Created on: 02.10.2016
 *      Author: imolcean
 */

#include "Timer.h"

namespace marco {

Timer::Timer(IOService& io, Func callback) : m_timer(io), m_callback(callback) {}

void Timer::start(Duration interval)
{
	m_timer.expires_from_now(interval);
	m_timer.async_wait(m_callback);
}

void Timer::stop()
{
	m_timer.cancel();
}

Timer::~Timer()
{
	stop();
}

} /* namespace marco */
