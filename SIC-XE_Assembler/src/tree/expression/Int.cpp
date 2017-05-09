/*
 * Int.cpp
 *
 *  Created on: 8 May 2017
 *      Author: heshamelsawaf
 */

#include "Int.h"

Int::Int(Location location, int value) :
		Expression("<int>", location) {
	this->value = value;
}

Int::~Int() {
	// TODO Auto-generated destructor stub
}

std::string Int::print() const {
	return std::to_string(value);
}

int Int::evaluate(Prog &program, Error** error) {
	return value;
}
