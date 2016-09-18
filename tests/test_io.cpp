/*
 * test_io.cpp
 *
 *  Created on: 18.09.2016
 *      Author: imolcean
 *
 *      Test for non-blocking console input using threads.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

typedef void (*func)();

std::mutex lock;
std::string buffer;
int i = 0;

void call()
{
	std::lock_guard<std::mutex> guard(lock);

	std::cout << "Command: " << buffer << std::endl << std::endl;
}

bool parse(std::string str)
{
	std::lock_guard<std::mutex> guard(lock);

	if(buffer == str || str.empty())
	{
		return false;
	}

	return true;
}

void inputHandler(func callback)
{
	std::string tmp;

	while(true)
	{
		std::cout << "Enter the command..." << std::endl;
		std::getline(std::cin, tmp);

		std::cout << "Cycle " << i << std::endl;

		if(parse(tmp))
		{
			{
				std::lock_guard<std::mutex> guard(lock);

				std::cout << "OK" << std::endl;
				buffer = tmp;
			}

			callback();
		}
		else
		{
			std::lock_guard<std::mutex> guard(lock);

			std::cout << "Failed" << std::endl << std::endl;
		}
	}
}

int main(int argc, char **argv)
{
	std::thread t(inputHandler, std::ref(call));

	while(true)
	{
		i++;
//		std::cout << "Cycle " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
