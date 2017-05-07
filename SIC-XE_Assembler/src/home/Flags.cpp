/*
 * Flags.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Flags.h"
#include "../SIC.h"

Flags::Flags() {
	this->rightMostTwoDigits = 0x00;
	this->x = 0x00;
}

Flags::~Flags() {
}

std::string Flags::print() const {
	std::string res = "--";
	res += (this->isIndexed() ? "x" : "-");
	return res;
}

std::string Flags::printOperand(std::string operand) const {
	if (this->isIndexed())
		return operand + ",X";
	return operand;
}

unsigned char Flags::combineWithOpCode(int opCode) const {
	return (unsigned char) (opCode & 0xFC);
}

int Flags::get_X() const {
	return (x & 0x80);
}

bool Flags::isIndexed() const {
	return (x & INDEXED) == INDEXED;
}

void Flags::setIndexed() {
	x |= INDEXED;
}

int Flags::getMinOperand() const {
	return SIC::MIN_SICADDR;
}

int Flags::getMaxOperand() const {
	return SIC::MAX_SICADDR;
}
