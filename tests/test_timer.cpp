/*
 * test_timer.cpp
 *
 *  Created on: 28.09.2016
 *      Author: imolcean
 */

#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

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
	Timer(IOService& io, Func callback) : m_timer(io), m_callback(callback)
	{
		std::cout << "TIMER CREATED" << std::endl;
	}

	void start(Duration interval)
	{
		if(m_timer.expires_from_now(interval) > 0)
		{
			std::cout << "CANCEL" << std::endl;
		}
		else
		{
			std::cout << "TOO LATE" << std::endl;
		}

		m_timer.async_wait(m_callback);
		std::cout << "START" << std::endl;
	}

	void stop()
	{
		m_timer.cancel();
		std::cout << "STOP" << std::endl;
	}

	~Timer()
	{
		stop();
	}
};

class Robot
{
public:
	Robot() {}

	void stop(const boost::system::error_code& e)
	{
		if(e != boost::asio::error::operation_aborted)
		{
			std::cout << "ROBOT_STOP" << std::endl;
		}
	}
};

boost::asio::io_service io;

void io_thread()
{
	boost::asio::io_service::work work(io);
	io.run();
}

Robot robot;
Timer timer(io, boost::bind(&Robot::stop, robot, boost::asio::placeholders::error));
int i;

int main(int argc, char **argv)
{
	std::thread th(&io_thread);

	while(1)
	{
		std::cin >> i;

		if(i == 0)
		{
			timer.stop();
		}
		else
		{
			timer.start(boost::posix_time::milliseconds(i));
		}
	}
}
