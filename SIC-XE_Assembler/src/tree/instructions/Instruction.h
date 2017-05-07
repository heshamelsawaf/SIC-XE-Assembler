/*
 * Instruction.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_INSTRUCTIONS_INSTRUCTION_H_
#define SRC_TREE_INSTRUCTIONS_INSTRUCTION_H_

#include "../../home/Mnemonic.h"
#include "../../asm/Location.h"
#include "../Command.h"
#include <string>

class Instruction: public Command {
public:
	virtual ~Instruction();
protected:
	Instruction(Location *location, std::string label, Mnemonic *mnemonic);
};

#endif /* SRC_TREE_INSTRUCTIONS_INSTRUCTION_H_ */
