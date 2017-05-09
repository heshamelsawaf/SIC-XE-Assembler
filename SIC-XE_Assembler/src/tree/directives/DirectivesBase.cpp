/*
 * DirectivesBase.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "DirectivesBase.h"

DirectivesBase::DirectivesBase(Location location, std::string label,
		Mnemonic *mnemonic, Expression *expression) :
		Directive(location, label, mnemonic) {
	this->value = 0;
	this->expression = expression;
}

DirectivesBase::~DirectivesBase() {
	// TODO Auto-generated destructor stub
}

std::string DirectivesBase::printOperand() const {
	return (expression == NULL) ? "" : expression->print();
}

int DirectivesBase::getValue() const {
	return this->value;
}

void DirectivesBase::resolve(Prog &program, Error** error) {
	value = expression == NULL ? -1 : expression->evaluate(program, error);
}

Expression &DirectivesBase::getExpression() const {
	return *(this->expression);
}
