/*
 * InstructionFormat3Extended.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "InstructionFormat3Extended.h"
#include "../../SIC.h"
#include "../Prog.h"

InstructionFormat3Extended::InstructionFormat3Extended(Location location,
		std::string label, Mnemonic *mnemonic, Flags *flags, int operand,
		std::string symbol) :
		InstructionFormat3Abstract(location, label, mnemonic, flags, operand,
				symbol) {
}

InstructionFormat3Extended::~InstructionFormat3Extended() {
}

void InstructionFormat3Extended::checkSymbol(Prog &program, Symbol *symbol,
		Error** error) const {

}

bool InstructionFormat3Extended::resolveAddressing(Prog &program) {
	if (this->resolvedSymbol == NULL || this->resolvedSymbol->isAbsolute()) {
		if (SIC::isDisp(this->value))
			return true;
	}
	if (SIC::isDisp(this->resolvedValue)) {
		return true;
	}
	return false;
}

int InstructionFormat3Extended::getCommandSize() const {
	return 3;
}

void InstructionFormat3Extended::burnObjectCode(unsigned char *data,
		int location, int length) const {
	data[location] = this->flags->combineWithOpCode(
			this->mnemonic->getOpCode());
	data[location + 1] = (unsigned char) (this->flags->get_X()
			| (resolvedValue >> 8) & 0x7F);
	data[location + 2] = (unsigned char) (resolvedValue & 0xFF);
}
