/*
 * Error.cpp
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#include "Error.h"
#include "Location.h"

Error::Error(Location location, std::string message) :
		location(location), message(message) {
}

Error::Error(const std::string message) :
		location(Location(0, 0, 0)), message(message) {
}

Error::~Error() {
}

std::string Error::getError() const {
	return this->message;
}

const Location& Error::getErrorLocation() const {
	return location;
}

int Error::Compare(const Error &error) const {
	return this->location.getPositon() - error.location.getPositon();
}

bool Error::operator ==(const Error &error) const {
	return !(this->Compare(error));
}
bool Error::operator <(const Error &error) const {
	return this->Compare(error) < 0;
}

std::string Error::print() const {
	std::string head = "Error"
			+ (location.getColumn() || location.getPositon()
					|| location.getRow() ?
					" at " + location.print() + " ("
							+ std::to_string(location.getPositon()) + ")" :
					"");
	return ((message.compare("")) ? (head + ": " + message) : head) + ".";
}
