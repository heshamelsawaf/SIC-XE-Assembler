/*
 * InstructionFormat3.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3_H_
#define SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3_H_

#include "../../home/Mnemonic.h"
#include "../../asm/Location.h"
#include "../../home/Flags.h"
#include "Instruction.h"

class InstructionFormat3: public Instruction {
public:
	InstructionFormat3(Location location, std::string label,
			Mnemonic *mnemonic);
	virtual ~InstructionFormat3();
	std::string printOperand() const;
	int getCommandSize() const;
	void burnObjectCode(std::vector<unsigned char>& vec, int location) const;
private:
	Flags *flags;
};

#endif /* SRC_TREE_INSTRUCTIONS_INSTRUCTIONFORMAT3_H_ */
