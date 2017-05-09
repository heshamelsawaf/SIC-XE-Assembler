/*
 * Expression.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Expression.h"
#include "../Prog.h"

Expression::Expression(std::string name, Location location) :
		location(location) {
	this->name = name;
}

Expression::~Expression() {
}

std::string Expression::print() const {
	return "";
}

Expression *Expression::getParsedExpression() {
	return this;
}

int Expression::evaluate(Prog &program, Error** error) {
	return 0;
}
