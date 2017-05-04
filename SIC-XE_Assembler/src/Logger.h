/*
 * Logger.h
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_LOGGE_H_
#define SRC_LOGGE_H_

#include <iostream>
#include <string>

class Logger {
public:
	Logger();
	virtual ~Logger();
	static void err(std::string errMsg);
};

#endif /* SRC_LOGGE_H_ */
