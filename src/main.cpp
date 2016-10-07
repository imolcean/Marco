/*
 * main.cpp
 *
 *  Created on: 20.09.2016
 *      Author: imolcean
 */

#include <thread>
#include <chrono>
#include <csignal>

#include <libconfig.h++>

#include "Robot.h"
#include "InputHandler.h"
#include "StreamListener.h"
#include "WSServer.h"
#include "Timer.h"

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace marco;

static const std::string LOG_CONFIG_PATH = "../config/log.conf";

Track* leftTrack;
Track* rightTrack;
Robot* robot;

InputHandler* handler;
StreamListener* console;
WSServer* web;

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

	delete handler;

	// TODO
//	io.stop();

	exit(signum);
}

int init(int argc, char** argv)
{
	// CONFIGURING THE LOGGER

	el::Configurations conf(LOG_CONFIG_PATH);
	el::Loggers::reconfigureLogger("default", conf);

	// READING THE CONFIG FILE

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

	// READING THE CONFIG PARAMETERS

	int leftPinA;
	int leftPinB;
	int leftPinE;

	int rightPinA;
	int rightPinB;
	int rightPinE;

	int port;
	bool web_logs;

	try
	{
		leftPinA = config.lookup("robot.tracks.left.pinA");
		leftPinB = config.lookup("robot.tracks.left.pinB");
		leftPinE = config.lookup("robot.tracks.left.pinE");

		rightPinA = config.lookup("robot.tracks.right.pinA");
		rightPinB = config.lookup("robot.tracks.right.pinB");
		rightPinE = config.lookup("robot.tracks.right.pinE");

		port = config.lookup("robot.web.port");
		web_logs = config.lookup("robot.web.logs");
	}
	catch(libconfig::SettingNotFoundException& e)
	{
		LOG(ERROR) << "Error at reading a setting" << std::endl;

		return -1;
	}

	// STARTING THE IO THREAD

	std::thread th_io(&io_thread);
	th_io.detach();
	// TODO Thread control, not just detach

	// OBJECT INITIALISATION

	leftTrack = new Track(leftPinA, leftPinB, leftPinE);
	rightTrack = new Track(rightPinA, rightPinB, rightPinE);
	robot = new Robot(*leftTrack, *rightTrack, io);

	handler = new InputHandler(*robot);
	console = new StreamListener(std::cin, std::bind(&InputHandler::handle, handler, std::placeholders::_1));
	web = new WSServer(io, std::bind(&InputHandler::handle, handler, std::placeholders::_1), port, web_logs);

	// STARTING THE INPUT THREADS

	std::thread th_console(&StreamListener::run, console);
	th_console.detach();
	// TODO Thread control, not just detach

	std::thread th_web(&WSServer::run, web);
	th_web.detach();
	// TODO Thread control, not just detach

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
