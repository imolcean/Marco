/*
 * main.cpp
 *
 *  Created on: 20.09.2016
 *      Author: imolcean
 */

#include <mutex>
#include <chrono>
#include <csignal>

#include <libconfig.h++>

#include "Robot.h"
#include "ControlEntity.h"
#include "InputHandler.h"

using namespace marco;

ControlEntity controlBuffer;
bool newCommand;
std::mutex lock;
InputHandler console(controlBuffer, newCommand, lock);

Track* leftTrack;
Track* rightTrack;
Robot* robot;

void deinit(int signum)
{
	delete robot;
	delete leftTrack;
	delete rightTrack;

	exit(signum);
}

int init(int argc, char** argv)
{
	// READING THE CONFIG

	int leftPinA;
	int leftPinB;
	int leftPinE;

	int rightPinA;
	int rightPinB;
	int rightPinE;

	std::string filename;
	libconfig::Config conf;

	if(argc > 1)
	{
		filename = argv[1];
	}
	else
	{
		std::cout << "No configuration file provided" << std::endl;
		return -1;
	}

	try
	{
		conf.readFile(filename.c_str());
	}
	catch(const libconfig::FileIOException& e)
	 {
		std::cout << "I/O error while reading file." << std::endl;
		return(-1);
	}
	catch(libconfig::ParseException& e)
	{
		std::cout << "Error: " << e.getError() << " in " << e.getFile() << ":" << e.getLine() << std::endl;
		return -1;
	}


	try
	{
		leftPinA = conf.lookup("robot.tracks.left.pinA");
		leftPinB = conf.lookup("robot.tracks.left.pinB");
		leftPinE = conf.lookup("robot.tracks.left.pinE");

		rightPinA = conf.lookup("robot.tracks.right.pinA");
		rightPinB = conf.lookup("robot.tracks.right.pinB");
		rightPinE = conf.lookup("robot.tracks.right.pinE");
	}
	catch(libconfig::SettingNotFoundException& e)
	{
		std::cout << "Error at reading a setting" << std::endl;
		return -1;
	}

	// OBJECT INITIALISATION

	leftTrack = new Track(leftPinA, leftPinB, leftPinE);
	rightTrack = new Track(rightPinA, rightPinB, rightPinE);
	robot = new Robot(*leftTrack, *rightTrack);

	// STARTING THE INPUT HANDLERS

	console.run();

	// REGISTER SIGNAL HANDLERS

	signal(SIGINT, deinit);
	signal(SIGTERM, deinit);

	return 0;
}

int loop()
{
	if(newCommand)
	{
		ControlEntity control;
		{
			std::lock_guard<std::mutex> guard(lock);

			control = controlBuffer;
			newCommand = false;
		}

		std::cout << "Command received" << std::endl;
		std::cout << "X: " << control.getX() << std::endl;
		std::cout << "Y: " << control.getY() << std::endl;
		std::cout << "T: " << control.getTime() << std::endl;
		std::cout << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return 0;
}

/**
 * Main function.
 */
int main(int argc, char **argv)
{
	int err;

	if((err = init(argc, argv)) != 0)
	{
		return err;
	}

	while(true)
	{
		if((err = loop()) != 0)
		{
			return err;
		}
	}

	return 0;
}
