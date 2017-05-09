/*
 * Prog.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Prog.h"

Prog::Prog() {
//	this->switchSection("");            // default section
	this->maxLabelLength = 3;
	this->addrsOfFirstInstruction = 0;
	this->cuurentSection = NULL;
	this->startAddress = 0;
	this->name = "";
	this->switchSection("");
}

Prog::~Prog() {
	for (unsigned int i = 0; i < this->sections.size(); i++)
		delete sections[i];
	this->sections.clear();
}

std::string Prog::getName() const {
	return this->name;
}

void Prog::setName(std::string name) {
	this->name = name;
}

int Prog::getStartAddress() const {
	return this->startAddress;
}

void Prog::setStartAddress(int address) {
	this->startAddress = address;
	this->setAddressOfFirstInstruction(address);
}

int Prog::getAddressOfFirstInstruction() const {
	return this->addrsOfFirstInstruction;
}

void Prog::setAddressOfFirstInstruction(int address) {
	this->addrsOfFirstInstruction = address;
}

Section &Prog::getCurrentSection() const {
	return *(this->cuurentSection);
}

Block &Prog::getCurrentBlock() const {
	return this->cuurentSection->getCurrentBlock();
}

int Prog::getLocationCounter() const {
	return this->getCurrentBlock().getLocationCounter();
}

void Prog::step(int stepSize) {
	this->getCurrentBlock().step(stepSize);
}

int Prog::getMaxLabelLength() const {
	return this->maxLabelLength;
}

int Prog::maxSymbolLength() const {
	int max = -1;
	for (Section *section : this->sections) {
		int len = section->getSectionName().length()
				+ section->getSymbols().getMaxSymbolIdentifierLength() + 1;
		if (len > max)
			max = len;
	}
	return max;
}

void Prog::flushAllLiterals() {
	for (Section *section : sections)
		section->getLiterals().flush(*this);
}

Section *Prog::findSection(std::string sectionName) {
	for (Section *section : sections)
		if (!section->getSectionName().compare(sectionName))
			return section;
	return NULL;
}

void Prog::switchSection(std::string sectionName) {
	this->cuurentSection = this->findSection(sectionName);
	if (this->cuurentSection == NULL) {
		this->cuurentSection = new Section(name);
		this->sections.push_back(this->cuurentSection);
	}
}

void Prog::switchDefault() {
	this->switchSection("");
	this->cuurentSection->switchBlock("");
}

void Prog::append(Command *command) {
	this->commands.push_back(command);         // add command to the program
	this->getCurrentBlock().append(command); // add command to the current block
	if (command->getLabel().length() > this->maxLabelLength)
		this->maxLabelLength = command->getLabel().length();
}

void Prog::enter(Prog &program, Error** error) {
	this->switchDefault();
}

std::vector<Command *> Prog::getCommands() const {
	return commands;
}

std::vector<Section *> Prog::getSections() const {
	return sections;
}
