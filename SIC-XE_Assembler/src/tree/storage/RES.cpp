/*
 * RES.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "RES.h"
#include "../../home/Opcode.h"

RES::RES(Location *loaction, std::string label, Mnemonic *mnemonic) :
		Storage(location, label, mnemonic) {
	this->count = 0;
}

RES::~RES() {
}

std::string RES::printOperand() const {
	return "";
}

int RES::getCommandSize() const {
	switch (this->mnemonic->getOpCode()) {
	case Opcode::RESB:
		return count;
	case Opcode::RESW:
		return 3 * count;
	}
	return 0;
}

void RES::resolve(Prog &program, Error *error) {
//TODO
}

void RES::burnObjectCode(unsigned char *data, int location, int length) const {
	int s = this->getCommandSize();
	if (s <= 0)
		return;
	unsigned char arr[s];
	for (int i = location; i < location + s; i++)
		arr[i] = (unsigned char) 0;
	data = arr;
}

