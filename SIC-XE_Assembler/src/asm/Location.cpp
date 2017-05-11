/*
 * Location.cpp
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#include "Location.h"

Location::Location(int position, int row, int column) :
		position(position), row(row), column(column) {
	// TODO Auto-generated constructor stub

}

Location::~Location() {
	// TODO Auto-generated destructor stub
}

int Location::getPositon() const {
	return this->position;
}

int Location::getRow() const {
	return this->row;
}

int Location::getColumn() const {
	return this->column;
}

std::string Location::print() const {
	return std::to_string(row) + ", " + std::to_string(column);
}
