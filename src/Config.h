/*
 * Config.h
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

namespace marco
{

class Config
{
private:
	std::string m_filename;

public:
	Config(std::string filename);
	void readConfig();
};

} /* namespace marco */

#endif /* CONFIG_H_ */
