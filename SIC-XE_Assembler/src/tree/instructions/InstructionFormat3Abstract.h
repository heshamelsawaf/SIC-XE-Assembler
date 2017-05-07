/*
 * InstructionFormat3Abstract.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3ABSTRACT_H_
#define SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3ABSTRACT_H_

#include "../../home/Flags.h"
#include "../../asm/Location.h"
#include "../../home/Mnemonic.h"
#include "../Symbol.h"
#include "Instruction.h"
#include <string>

class InstructionFormat3Abstract: public Instruction {
public:
	virtual ~InstructionFormat3Abstract();
	virtual std::string printOperand() const;
	void setSymbol(std::string symbol);
	virtual void checkSymbol(Prog &program, Symbol *symbol, Error *error) const;
	virtual bool resolveAddressing(Prog &program);
	void resolve(Prog &program, Error *error);
	Location *getLocation() const;
	Mnemonic *getMnemonic() const;
	std::string getSymbol() const;

private:
	bool operandIsValue() const;

protected:
	InstructionFormat3Abstract(Location *location, std::string label,
			Mnemonic *mnemonic, Flags *flags, int value, std::string symbol);
	Flags *flags;
	Symbol *resolvedSymbol;
	int value;
	std::string symbol;
	int resolvedValue;

};

#endif /* SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3ABSTRACT_H_ */
