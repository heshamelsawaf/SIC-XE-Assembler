/*
 * LiteralInstruction.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "LiteralInstruction.h"
#include "../Prog.h"

LiteralInstruction::LiteralInstruction(InstructionFormat3Abstract *command,
		StorageData *literal) :
		Instruction(command->getLocation(), command->getLabel(),
				command->getMnemonic()) {
	this->command = command;
	this->literal = literal;
}

LiteralInstruction::~LiteralInstruction() {
	delete this->command;
	this->command = NULL;
}

InstructionFormat3Abstract &LiteralInstruction::getCommand() const {
	return *(this->command);
}

std::string LiteralInstruction::print() const {
	return this->command->print() + " " + this->printOperand();
}

void LiteralInstruction::append(Prog &program, Error** error) {
	*error = NULL;
	this->enter(program, error);
	if (*error != NULL)
		return;
	StorageData *lit = program.getCurrentSection().getLiterals().find(
			*(this->literal));
	if (lit != NULL)
		this->literal = lit;
	else
		program.getCurrentSection().getLiterals().append(this->literal);
	this->command->setSymbol(this->literal->getLabel());
	program.append(this);       // add command to the current block
	*error = NULL;
	this->leave(program, error);
}

std::string LiteralInstruction::printOperand() const {
	return this->command->getSymbol() + " (" + this->literal->print() + ")";
}

int LiteralInstruction::getCommandSize() const {
	if (command == NULL)
		return 3;
	return command->getCommandSize();
}

void LiteralInstruction::burnObjectCode(unsigned char *data, int location,
		int length) const {
	command->burnObjectCode(data, location, length);
}
