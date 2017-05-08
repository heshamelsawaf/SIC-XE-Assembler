/*
 * Expression.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Expression.h"
#include "../Prog.h"

Expression::Expression(std::string name, Location *location) {
	this->name = name;
	this->location = location;
}

Expression::~Expression() {
	delete this->location;
	this->location = NULL;
}

std::string Expression::print() const {
	return "";
}

Expression *Expression::getParsedExpression() {
	return this;
}

int Expression::evaluate(Prog &program, Error *error) {
	return 0;
}
