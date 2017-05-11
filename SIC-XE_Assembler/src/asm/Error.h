/*
 * Error.h
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_ASM_ERROR_H_
#define SRC_ASM_ERROR_H_

#include "Location.h"
#include <string>

class Error {
public:
	Error(Location location, std::string message);
	Error(std::string message);
	virtual ~Error();
	std::string print() const;
	int Compare(const Error &error) const;
	bool operator ==(const Error &error) const;
	bool operator <(const Error &error) const;
	std::string getError() const;
	const Location& getErrorLocation() const;
private:
	Location location;
	std::string message;
};

#endif /* SRC_ASM_ERROR_H_ */
