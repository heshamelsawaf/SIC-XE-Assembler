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
#include <string>
#include <vector>

class Section: public Node {
public:
	Section(std::string sectionName);
	virtual ~Section();
	std::string print() const;
	std::string getSectionName() const;
	bool isDefaultSection() const;
	int getSectionSize() const;
	void setSectionSize(int sectionSize);
	void reset();
	Block &getCurrentBlock() const;
	void switchBlock(std::string blockName);
	Symbols &getSymbols() const;
	Literals &getLiterals() const;
	void enter(Prog &program, Error** error);
	std::vector<Block *> getBlocks() const;

private:
	int sectionSize;
	std::string sectionName;
	std::vector<Block *> blocks;
	Symbols *symbols;
	Literals *literals;
	Block *currentBlock;
	Block *findBlock(std::string blockName);

};

#endif /* SRC_TREE_SECTION_H_ */
