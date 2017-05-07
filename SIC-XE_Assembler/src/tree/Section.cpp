/*
 * Section.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Section.h"
#include "Prog.h"

Section::Section(std::string sectionName) :
		Node() {
	this->sectionName = sectionName;
	this->symbols = new Symbols();
	this->literals = new Literals();
	this->reset();
	this->sectionSize = 0;
	this->currentBlock = NULL;
}

Section::~Section() {
	delete this->symbols;
	delete this->literals;
	this->symbols = NULL;
	this->literals = NULL;
	for (unsigned int i = 0; i < this->blocks.size(); i++)
		delete blocks[i];
	this->blocks.clear();
}

std::string Section::getSectionName() const {
	return (this->isDefaultSection() ? "<default>" : this->sectionName);
}

bool Section::isDefaultSection() const {
	return (this->sectionName.compare("") ? false : true);
}

void Section::setSectionSize(int sectionSize) {
	this->sectionSize = sectionSize;
}

int Section::getSectionSize() const {
	return this->sectionSize;
}

void Section::reset() {
	this->switchBlock("");
}

Block &Section::getCurrentBlock() const {
	return *(this->currentBlock);
}

Block *Section::findBlock(std::string blockName) {
	for (Block *block : this->blocks)
		if (!(block->getBlockName().compare(blockName)))
			return block;
	return NULL;
}

void Section::switchBlock(std::string blockName) {
	this->currentBlock = this->findBlock(blockName);
	if (this->currentBlock == NULL) {
		this->currentBlock = new Block(blockName);
		this->blocks.push_back(this->currentBlock);
	}
}

Symbols &Section::getSymbols() const {
	return *(this->symbols);
}

Literals &Section::getLiterals() const {
	return *(this->literals);
}

void Section::addRelocation(Relocation *relocation) {
	this->relocations.push_back(relocation);
}

void Section::addRelocation(int address, int length) {
	this->addRelocation(new Relocation(address, length));
}

void Section::enter(Prog &program, Error *error) {
	program.switchSection(this->getSectionName());
	program.getCurrentSection().switchBlock("");
}
