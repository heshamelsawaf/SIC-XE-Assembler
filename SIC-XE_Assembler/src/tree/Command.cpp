/*
 * Command.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Command.h"
#include "Prog.h"
#include "../Conversion.h"

Command::Command(Location location, std::string label, Mnemonic *mnemonic) :
		location(location) {
	this->label = label;
	this->mnemonic = mnemonic;
	this->comment = "";
	this->type = "";
}

Command::~Command() {
	delete this->mnemonic;
	this->mnemonic = NULL;
}

std::string Command::print() const {
	return this->printMnemonicName() + " " + this->printOperand();
}

void Command::enter(Prog &program, Error** error) {
	program.step(this->getCommandSize());
	*error = NULL;
}

void Command::append(Prog &program, Error** error) {
	this->enter(program, error);
	program.append(this);
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
	return location;
}

std::string Command::getType() const {
	return this->type;
}

std::vector<unsigned char> Command::burnObjectCode() const {
	std::vector<unsigned char> vec(this->getCommandSize());
	this->burnObjectCode(vec, 0);
	return vec;
}

std::string Command::burnText(std::string buffer) {
	if (this->getCommandSize() > 0) {
		std::vector<unsigned char> vec = this->burnObjectCode();
		buffer += Conversion::bytesToHex(vec);
	}
	return buffer;
}

std::string Command::printOperand() const {
	return "";
}
int Command::getCommandSize() const {
	return 0;
}

void Command::burnObjectCode(std::vector<unsigned char>& vec,
		int location) const {

}
