/*
 * InstructionFormat3Extended.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3EXTENDED_H_
#define SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3EXTENDED_H_

#include "InstructionFormat3Abstract.h"
#include "../../home/Mnemonic.h"
#include "../../asm/Location.h"
#include "../../home/Flags.h"
#include <string>

class InstructionFormat3Extended: public InstructionFormat3Abstract {
public:
	InstructionFormat3Extended(Location location, std::string label,
			Mnemonic *mnemonic, Flags *flags, int operand, std::string symbol);
	virtual ~InstructionFormat3Extended();
	void checkSymbol(Prog &program, Symbol *symbol, Error** error) const;
	bool resolveAddressing(Prog &program);
	int getCommandSize() const;
	void burnObjectCode(unsigned char *data, int location, int length) const;
};

#endif /* SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3EXTENDED_H_ */
