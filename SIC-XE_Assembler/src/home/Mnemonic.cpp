/*
 * Mnemonic.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include "Mnemonic.h"

Mnemonic::Mnemonic(std::string name, int opCode, int type) :
		name(name), opCode(opCode), type(type) {
}

Mnemonic::~Mnemonic() {
	// TODO Auto-generated destructor stub
}

std::string Mnemonic::getName() const {
	return this->name;
}

int Mnemonic::getType() const {
	return this->type;
}

int Mnemonic::getOpCode() const {
	return this->opCode;
}
