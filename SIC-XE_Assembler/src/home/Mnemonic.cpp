/*
 * Mnemonic.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include "Mnemonic.h"

Mnemonic::Mnemonic(const std::string name, const int opCode) :
		name(name), opCode(opCode) {

}

Mnemonic::~Mnemonic() {
	// TODO Auto-generated destructor stub
}

const std::string Mnemonic::getName() const {
	return this->name;
}
