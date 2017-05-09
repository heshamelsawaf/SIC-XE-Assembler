/*
 * Data.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Data.h"
#include "../../parser/Parser.h"
#include "../../home/Opcode.h"

Data::Data(int opcode) {
	this->opCode = opcode;
	this->next = NULL;
}

Data::~Data() {
	while (this->next != NULL) {
		Data *temp = this->next->getNext();
		delete this->next;
		this->next = temp;
	}
	this->next = NULL;
}

std::string Data::print() const {
	return (this->next == NULL) ? "" : "," + this->next->print();
}

void Data::parse(Parser &parser, bool allowList, Error** error) {
	if (allowList && parser.skipIfComma())
		this->next = parser.getOperandParser().parseData(this->opCode, true,
				error);
}

bool Data::operator ==(const Data &dta) const {
	if (opCode != dta.getOpCode())
		return false;  // distinguish BYTE,WORD,FLOaT
	if (this->data.size() != dta.getData().size())
		return false;
	for (int i = 0; i < data.size(); i++)
		if (data[i] != dta.getData()[i])
			return false;
	if (next == NULL && dta.getNext() == NULL)
		return true;
	if (next != NULL && dta.getNext() != NULL)
		return this->next == dta.getNext();
	return false;
}

int Data::sizes() const {
	switch (this->opCode) {
	case Opcode::BYTE:
		return data.size();
	case Opcode::WORD:
		return (data.size() + 2) / 3 * 3;
	}
	return 0;
}

int Data::getSize() const {
	int s = this->sizes();
	if (this->next != NULL)
		s += this->next->getSize();
	return s;
}

int Data::getOpCode() const {
	return this->opCode;
}

const std::vector<unsigned char>& Data::getData() const {
	return data;
}

Data *Data::getNext() const {
	return this->next;
}

void Data::burnObjectCode(std::vector<unsigned char>& vec, int location) const {
	int i;
	for (i = 0; i < data.size(); i++)
		vec[location + i] = data[i];
	int s = this->sizes();
	for (; i < s; i++)
		vec[i] = 0;
	if (this->next != NULL)
		this->next->burnObjectCode(vec, location + s);
}
