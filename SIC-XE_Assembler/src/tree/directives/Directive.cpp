/*
 * Directive.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Directive.h"

Directive::Directive(Location *location, std::string label, Mnemonic *mnemonic) :
		Command(location, label, mnemonic) {
	this->type = "Directive";
}

Directive::~Directive() {
	// TODO Auto-generated destructor stub
}

std::string Directive::printOperand() const {
	return "";
}
int Directive::getCommandSize() const {
	return 0;
}
void Directive::burnObjectCode(unsigned char *data, int location,
		int length) const {
}
