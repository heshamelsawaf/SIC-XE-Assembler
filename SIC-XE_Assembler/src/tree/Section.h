/*
 * Section.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_SECTION_H_
#define SRC_TREE_SECTION_H_

#include "Node.h"
#include "Block.h"
#include "Symbols.h"
#include "Literals.h"
#include "Relocation.h"
#include <string>
#include <vector>

class Section: public Node {
public:
	Section(std::string sectionName);
	virtual ~Section();
	std::string getSectionName() const;
	bool isDefaultSection() const;
	int getSectionSize() const;
	void setSectionSize(int sectionSize);
	void reset();
	Block &getCurrentBlock() const;
	void switchBlock(std::string blockName);
	void addRelocation(int address, int length);
	Symbols &getSymbols() const;
	Literals &getLiterals() const;
	void enter(Prog &program, Error *error);

private:
	int sectionSize;
	std::string sectionName;
	std::vector<Block *> blocks;
	std::vector<Relocation *> relocations;
	Symbols *symbols;
	Literals *literals;
	Block *currentBlock;
	Block *findBlock(std::string blockName);
	void addRelocation(Relocation *relocation);

};

#endif /* SRC_TREE_SECTION_H_ */
