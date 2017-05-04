/*
 * Logger.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include "Logger.h"

Logger::Logger() {
	// TODO Auto-generated constructor stub

}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::err(std::string errMsg) {
	std::cerr << errMsg << "\n";
}
