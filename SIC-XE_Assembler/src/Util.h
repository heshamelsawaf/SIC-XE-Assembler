/*
 * Util.h
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <string>
#include <fstream>

class Util {
public:
	Util();
	virtual ~Util();
	static std::string readFile(std::ifstream* file);
	static std::string readFile(const std::string* file);
	static std::string getFileName(const std::string* file);
};

#endif /* SRC_UTIL_H_ */
