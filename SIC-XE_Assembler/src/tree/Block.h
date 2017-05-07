/*
 * Block.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_BLOCK_H_
#define SRC_TREE_BLOCK_H_

#include "Command.h"
#include "Node.h"
#include <string>
#include <vector>

class Block: public Node {
public:
	Block(std::string blockName);
	virtual ~Block();
	std::string getBlockName() const;
	bool isDefaultBlock() const;
	void append(Command &command);
	int getInstructionCounter() const;
	int getDirectiveCounter() const;
	int getStorageCounter() const;
	void reset();
	int getBlockStartAddress() const;
	void setBlockStartAddress(int blockStartAddress);
	int getLocationCounter() const;
	void setLocationCounter(int address);
	int getNextLocationCounter() const;
	void step(int stepSize);
	int getBlockSize() const;
	void enter(Prog &program, Error *error);
	void leave(Prog &program, Error *error);

private:
	std::string blockName;
	std::vector<Command> commands;
	int instructionCounter;
	int directiveCounter;
	int storageCounter;
	int blockStartAddress;
	int locationCounter;
	int nextLocationCounter;
	int previousLocationCounter;
	int blockSize;
};

#endif /* SRC_TREE_BLOCK_H_ */
