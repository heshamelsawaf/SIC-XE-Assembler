/*
 * LiteralInstruction.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_INSTRUCTIONS_LITERALINSTRUCTION_H_
#define SRC_TREE_INSTRUCTIONS_LITERALINSTRUCTION_H_

#include "InstructionFormat3Abstract.h"
#include "../storage/StorageData.h"
#include "Instruction.h"

class LiteralInstruction: public Instruction {
public:
	LiteralInstruction(InstructionFormat3Abstract *command,
			StorageData *literal);
	virtual ~LiteralInstruction();
	InstructionFormat3Abstract &getCommand() const;
	std::string print() const;
	void append(Prog &program, Error** error);
	std::string printOperand() const;
	int getCommandSize() const;
	void burnObjectCode(unsigned char *data, int location, int length) const;

protected:
	StorageData *literal;

private:
	InstructionFormat3Abstract *command;

};

#endif /* SRC_TREE_INSTRUCTIONS_LITERALINSTRUCTION_H_ */
