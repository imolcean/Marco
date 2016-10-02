/*
 * main.cpp
 *
 *  Created on: 20.09.2016
 *      Author: imolcean
 */

#include <chrono>
#include <csignal>

#include <libconfig.h++>

#include "Robot.h"
#include "InputHandler.h"
#include "Timer.h"

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace marco;

static const std::string LOG_CONFIG_PATH = "../config/log.conf";

Track* leftTrack;
Track* rightTrack;
Robot* robot;

InputHandler* console;

libconfig::Config config;
boost::asio::io_service io;

void io_thread()
{
	boost::asio::io_service::work work(io);
	io.run();
}

void deinit(int signum)
{
	delete robot;
	delete leftTrack;
	delete rightTrack;

	delete console;

	exit(signum);
}

int init(int argc, char** argv)
{
	// CONFIGURING THE LOGGER

	el::Configurations conf(LOG_CONFIG_PATH);
	el::Loggers::reconfigureLogger("default", conf);

	// READING THE CONFIG

	int leftPinA;
	int leftPinB;
	int leftPinE;

	int rightPinA;
	int rightPinB;
	int rightPinE;

	std::string filename;

	if(argc > 1)
	{
		filename = argv[1];
	}
	else
	{
		LOG(ERROR) << "No configuration file provided" << std::endl;

		return -1;
	}

	try
	{
		config.readFile(filename.c_str());
	}
	catch(const libconfig::FileIOException& e)
	 {
		LOG(ERROR) << "I/O error while reading file." << std::endl;

		return -1;
	}
	catch(libconfig::ParseException& e)
	{
		LOG(ERROR) << "Error: " << e.getError() << " in " << e.getFile() << ":" << e.getLine() << std::endl;

		return -1;
	}


	try
	{
		leftPinA = config.lookup("robot.tracks.left.pinA");
		leftPinB = config.lookup("robot.tracks.left.pinB");
		leftPinE = config.lookup("robot.tracks.left.pinE");

		rightPinA = config.lookup("robot.tracks.right.pinA");
		rightPinB = config.lookup("robot.tracks.right.pinB");
		rightPinE = config.lookup("robot.tracks.right.pinE");
	}
	catch(libconfig::SettingNotFoundException& e)
	{
		LOG(ERROR) << "Error at reading a setting" << std::endl;

		return -1;
	}

	// OBJECT INITIALISATION

	leftTrack = new Track(leftPinA, leftPinB, leftPinE);
	rightTrack = new Track(rightPinA, rightPinB, rightPinE);
	robot = new Robot(*leftTrack, *rightTrack, io);

	// STARTING THE IO THREAD

	std::thread th(&io_thread);
	th.detach();
	// TODO Thread control, not just detach

	// STARTING THE INPUT HANDLERS

	console = new InputHandler(*robot);
	console->run();

	// REGISTER SIGNAL HANDLERS

	signal(SIGINT, deinit);
	signal(SIGTERM, deinit);

	return 0;
}

int loop()
{
	// TODO

//	std::cout << "Tick" << std::endl;
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
