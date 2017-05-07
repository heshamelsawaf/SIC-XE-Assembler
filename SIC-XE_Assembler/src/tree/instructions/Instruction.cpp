/*
 * Instruction.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Instruction.h"

Instruction::Instruction(Location *location, std::string label,
		Mnemonic *mnemonic) :
		Command(location, label, mnemonic) {
	this->type = "Instruction";
}

Instruction::~Instruction() {
}

