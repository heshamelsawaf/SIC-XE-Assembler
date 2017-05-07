/*
 * DirectivesBase.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "DirectivesBase.h"

DirectivesBase::DirectivesBase(Location *location, std::string label,
		Mnemonic *mnemonic) :
		Directive(location, label, mnemonic) {
	this->value = 0;
}

DirectivesBase::~DirectivesBase() {
	// TODO Auto-generated destructor stub
}

std::string DirectivesBase::printOperand() const {
	return "";
}

int DirectivesBase::getValue() const {
	return this->value;
}

void DirectivesBase::resolve(Prog &program) {
	this->value = -1;
}
