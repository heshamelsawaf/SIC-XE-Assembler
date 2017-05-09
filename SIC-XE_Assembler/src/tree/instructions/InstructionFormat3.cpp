/*
 * InstructionFormat3.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "InstructionFormat3.h"

InstructionFormat3::InstructionFormat3(Location location, std::string label,
		Mnemonic *mnemonic) :
		Instruction(location, label, mnemonic) {
	this->flags = new Flags();
}

InstructionFormat3::~InstructionFormat3() {
	delete this->flags;
	this->flags = NULL;
}

std::string InstructionFormat3::printOperand() const {
	return "";
}

int InstructionFormat3::getCommandSize() const {
	return 3;
}

void InstructionFormat3::burnObjectCode(std::vector<unsigned char>& vec,
		int location) const {
	vec[location] = this->flags->combineWithOpCode(this->mnemonic->getOpCode());
	vec[location + 1] = 0;
	vec[location + 2] = 0;
}

