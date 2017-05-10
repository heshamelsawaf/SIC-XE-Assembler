/*
 * RES.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "RES.h"
#include "../../home/Opcode.h"

RES::RES(Location location, std::string label, Mnemonic *mnemonic,
		Expression *expression) :
		Storage(location, label, mnemonic) {
	this->count = 0;
	this->expression = expression;
}

RES::~RES() {
	delete expression;
	expression = NULL;
}

std::string RES::printOperand() const {
	return expression->print();
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

void RES::resolve(Prog &program, Error** error) {
	count = expression->evaluate(program, error);
}

void RES::burnObjectCode(std::vector<unsigned char>& vec, int location) const {
	int s = this->getCommandSize();
	if (s <= 0)
		return;
	for (int i = location; i < location + s; i++)
		vec[i] = (unsigned char) 0;
}

bool RES::burnText(std::string& buffer) {
	return true;
}
