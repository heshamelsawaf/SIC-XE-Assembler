/*
 * Comment.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Comment.h"

Comment::Comment(Location *location, std::string comment) :
		Command(location, "", NULL) {
	this->setComment(comment);
}

Comment::~Comment() {
	// TODO Auto-generated destructor stub
}

std::string Comment::print() const {
	return this->getComment();
}

std::string Comment::printOperand() const {
	return "";
}

int Comment::getCommandSize() const {
	return 0;
}

void Comment::burnObjectCode(unsigned char *data, int location,
		int length) const {

}
