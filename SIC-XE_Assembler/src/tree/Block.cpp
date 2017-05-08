/*
 * Block.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Block.h"
#include "Prog.h"

Block::Block(std::string blockName) {
	this->blockName = blockName;
	this->instructionCounter = 0;
	this->directiveCounter = 0;
	this->storageCounter = 0;
	this->blockStartAddress = 0;
	this->locationCounter = 0;
	this->nextLocationCounter = 0;
	this->previousLocationCounter = 0;
	this->blockSize = 0;
}

Block::~Block() {
	// TODO Auto-generated destructor stub
}

std::string Block::getBlockName() const {
	return this->isDefaultBlock() ? "<default>" : this->blockName;
}

bool Block::isDefaultBlock() const {
	return (this->blockName.compare("") ? false : true);
}

void Block::append(Command *command) {
	this->commands.push_back(command);
	if (!(command->getType().compare("Instruction")))
		instructionCounter++;
	if (!(command->getType().compare("Directive")))
		directiveCounter++;
	if (!(command->getType().compare("Storage")))
		storageCounter++;
}

int Block::getInstructionCounter() const {
	return this->instructionCounter;
}

int Block::getDirectiveCounter() const {
	return this->directiveCounter;
}

int Block::getStorageCounter() const {
	return this->storageCounter;
}

void Block::reset() {
	this->setLocationCounter(this->blockStartAddress);
	this->previousLocationCounter = -1;
}

int Block::getBlockStartAddress() const {
	return this->blockStartAddress;
}

void Block::setBlockStartAddress(int blockStartAddress) {
	this->blockStartAddress = blockStartAddress;
	this->setLocationCounter(blockStartAddress);
}

int Block::getLocationCounter() const {
	return this->locationCounter;
}

void Block::setLocationCounter(int address) {
	this->locationCounter = this->nextLocationCounter = address;
}

int Block::getNextLocationCounter() const {
	return this->nextLocationCounter;
}

void Block::step(int stepSize) {
	this->locationCounter = this->nextLocationCounter;
	nextLocationCounter += stepSize;
}

int Block::getBlockSize() const {
	return this->blockSize;
}

void Block::enter(Prog &program, Error *error) {
	program.getCurrentSection().switchBlock(this->blockName);
}

void Block::leave(Prog &program, Error *error) {
	this->blockSize = this->nextLocationCounter - this->blockStartAddress;
}
