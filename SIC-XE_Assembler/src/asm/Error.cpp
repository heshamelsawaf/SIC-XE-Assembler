/*
 * Error.cpp
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#include "Error.h"
#include "Location.h"

Error::Error(Location *location, std::string message) {
	this->location = location;
	this->message = message;
}

Error::Error(std::string message) {
	this->location = new Location(0, 0, 0);
	this->message = message;
}

Error::~Error() {
	delete this->location;
}

std::string Error::getError() const {
	return this->message;
}

Location& Error::getErrorLocation() const {
	return *this->location;
}

int Error::Compare(const Error &error) const {
	return this->location->getPositon() - error.location->getPositon();
}

bool Error::operator ==(const Error &error) const {
	return !(this->Compare(error));
}
bool Error::operator <(const Error &error) const {
	return this->Compare(error) < 0;
}

