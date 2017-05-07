/*
 * Prog.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_PROG_H_
#define SRC_TREE_PROG_H_

#include "../asm/Error.h"
#include "Node.h"
#include "Block.h"
#include "Command.h"
#include "Section.h"
#include <string>
#include <vector>

class Prog: public Node {
public:
	Prog();
	virtual ~Prog();
	std::string getName() const;
	void setName(std::string name);
	int getStartAddress() const;
	void setStartAddress(int address);
	int getAddressOfFirstInstruction() const;
	void setAddressOfFirstInstruction(int address);
	Section &getCurrentSection() const;
	Block &getCurrentBlock() const;
	int getLocationCounter() const;
	void step(int stepSize);
	int getMaxLabelLength() const;
	int maxSymbolLength() const;
	void flushAllLiterals();
	void switchSection(std::string sectionName);
	void switchDefault();
	void append(Command &command);
	void enter(Prog &program, Error *error);

private:
	std::string name;
	int startAddress;
	int addrsOfFirstInstruction;
	int maxLabelLength;
	std::vector<Command> commands;
	std::vector<Section *> sections;
	Section *cuurentSection;
	Section *findSection(std::string sectionName);
};

#endif /* SRC_TREE_PROG_H_ */
