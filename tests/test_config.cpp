/*
 * test-config.cpp
 *
 *  Created on: 16.09.2016
 *      Author: imolcean
 */

#include <libconfig.h++>
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
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

	// READING CONFIG
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

	//

	std::string version;

	std::string windowTitle;
	int windowW;
	int windowH;

	std::string robotName;
	std::vector<std::string> creators;

	std::string robotChassisType;
	int robotChassisLength;
	int robotChassisWidth;
	int robotChassisHeight;
	std::string robotChassisMeasure;

	// READING SETTINGS
	try
	{
		version = conf.lookup("version").c_str();
	}
	catch(libconfig::SettingNotFoundException& e)
	{
		std::cout << "Error at reading the setting " << "Version" << std::endl;
		return -1;
	}

	try
	{
		windowTitle = conf.lookup("application.window.title").c_str();
		windowH = conf.lookup("application.window.size.h");
		windowW = conf.lookup("application.window.size.w");
	}
	catch(libconfig::SettingNotFoundException& e)
	{
		std::cout << "Error at reading the setting " << "Window" << std::endl;
		return -1;
	}

	try
	{
		robotName = conf.lookup("robot.name").c_str();
		libconfig::Setting& authors = conf.lookup("robot.authors");

		for(int i = 0; i < authors.getLength(); i++)
		{
			libconfig::Setting& author = authors[i];
			creators.push_back(author.c_str());
		}
	}
	catch(libconfig::SettingNotFoundException& e)
	{
		std::cout << "Error at reading the setting " << "Robot" << std::endl;
		return -1;
	}

	try
	{
		robotChassisType = conf.lookup("robot.chassis.type").c_str();
		robotChassisLength = conf.lookup("robot.chassis.length");
		robotChassisWidth = conf.lookup("robot.chassis.width");
		robotChassisHeight = conf.lookup("robot.chassis.height");
		robotChassisMeasure = conf.lookup("robot.chassis.measure").c_str();
	}
	catch(libconfig::SettingNotFoundException& e)
	{
		std::cout << "Error at reading the setting " << "Chassis" << std::endl;
		return -1;
	}

	//

	// OUTPUT
	std::cout << "Version: " << version << std::endl;

	std::cout << std::endl;

	std::cout << "Application: " << windowTitle << " " << windowW << "x" << windowH << std::endl;

	std::cout << std::endl;

	std::cout << "Robot: " << robotName << " made by ";
	for(std::string creator : creators)
	{
		std::cout << creator << ", ";
	}
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << "Chassis type: " << robotChassisType << std::endl;
	std::cout << "Chassis measures: " << robotChassisLength << "x" << robotChassisWidth
			<< "x" << robotChassisHeight << " (" << robotChassisMeasure << ")" << std::endl;

	std::cout << std::endl;

	//

	return 0;
}
