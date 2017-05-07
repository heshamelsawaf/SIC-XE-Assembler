/*
 * Command.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Command.h"
#include "Prog.h"
#include "../Conversion.h"

Command::Command(Location *location, std::string label, Mnemonic *mnemonic) {
	this->location = location;
	this->label = label;
	this->mnemonic = mnemonic;
	this->comment = "";
	this->type = "";
}

Command::~Command() {
	delete this->mnemonic;
	delete this->location;
	this->mnemonic = NULL;
	this->location = NULL;
}

std::string Command::print() const {
	return this->printMnemonicName() + " " + this->printOperand();
}

void Command::enter(Prog &program, Error *error) {
	program.step(this->getCommandSize());
	error = NULL;
}

void Command::append(Prog &program, Error *error) {
	this->enter(program, error);
	program.append(*this);
	this->leave(program, error);
}

bool Command::hasLabel() const {
	return (this->label.compare("") != 0);
}

std::string Command::getLabel() const {
	return this->label;
}

void Command::setComment(std::string comment) {
	if (comment.compare("")) {
		size_t first = comment.find_first_not_of(' ');
		if (std::string::npos != first) {
			size_t last = comment.find_last_not_of(' ');
			comment = comment.substr(first, (last - first + 1));

		}
	}
	this->comment = comment;
}

std::string Command::getComment() const {
	if (!(this->comment.compare("")))
		return "";
	return (comment[0] == '.' ? "." : ". ") + this->comment;
}

std::string Command::printMnemonicName() const {
	return this->mnemonic->getName();
}

Location &Command::getLocation() {
	return *(this->location);
}

std::string Command::getType() const {
	return this->type;
}

void Command::burnObjectCode(unsigned char *data) const {
	this->burnObjectCode(data, 0, this->getCommandSize());
}

std::string Command::burnText(std::string buffer) {
	if (this->getCommandSize() > 0) {
		unsigned char arr[this->getCommandSize()];
		this->burnObjectCode(arr);
		buffer += Conversion::bytesToHex(arr, this->getCommandSize());
	}
	return buffer;
}

std::string Command::printOperand() const {
	return "";
}
int Command::getCommandSize() const {
	return 0;
}

void Command::burnObjectCode(unsigned char *data, int location,
		int length) const {

}
