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

Location *Location::clone() const {
	return new Location(this->position, this->row, this->column);
}
