/*
 * InstructionFormat3Abstract.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "InstructionFormat3Abstract.h"
#include "../Prog.h"

InstructionFormat3Abstract::InstructionFormat3Abstract(Location location,
		std::string label, Mnemonic *mnemonic, Flags *flags, int value,
		std::string symbol) :
		Instruction(location, label, mnemonic) {
	this->flags = flags;
	this->value = value;
	this->symbol = symbol;
	this->resolvedSymbol = NULL;
	this->resolvedValue = 0;
}

InstructionFormat3Abstract::~InstructionFormat3Abstract() {
	delete this->flags;
	delete this->resolvedSymbol;
	this->flags = NULL;
	this->resolvedSymbol = NULL;
}

bool InstructionFormat3Abstract::operandIsValue() const {
	return (this->symbol.compare("") == 0);
}

std::string InstructionFormat3Abstract::printOperand() const {
	std::string op =
			this->operandIsValue() ? std::to_string(this->value) : this->symbol;
	return this->flags->printOperand(op);
}

void InstructionFormat3Abstract::setSymbol(std::string symbol) {
	this->symbol = symbol;
}

void InstructionFormat3Abstract::resolve(Prog &program, Error** error) {
	// resolve operand: value or symbol
	if (this->operandIsValue()) {
		this->resolvedValue = value;
		this->resolvedSymbol = NULL;
	} else {
		this->resolvedSymbol =
				program.getCurrentSection().getSymbols().getSymbol(
						this->symbol);
		if (this->resolvedSymbol == NULL) {
			std::string errMsg = "Undefined symbol '" + this->symbol + ",!";
			*error = new Error(this->getLocation(), errMsg);
			return;
		}
		*error = NULL;
		this->checkSymbol(program, this->resolvedSymbol, error);
		if (*error != NULL)
			return;
		this->resolvedValue = this->resolvedSymbol->getValue();
	}

	if (this->resolveAddressing(program))
		return;
	std::string errMsg = "Cannot address symbol '" + this->symbol + ",!";
	*error = new Error(this->getLocation(), errMsg);
	return;
}

Location& InstructionFormat3Abstract::getLocation() const {
	return this->location;
}

Mnemonic *InstructionFormat3Abstract::getMnemonic() const {
	return this->mnemonic;
}

std::string InstructionFormat3Abstract::getSymbol() const {
	return this->symbol;
}

void InstructionFormat3Abstract::checkSymbol(Prog &program, Symbol *symbol,
		Error** error) const {

}
bool InstructionFormat3Abstract::resolveAddressing(Prog &program) {
	return true;
}
