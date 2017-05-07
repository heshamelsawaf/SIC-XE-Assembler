/*
 * Num.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Num.h"
#include "../../home/Opcode.h"
#include "../../parser/Parser.h"

Num::Num(int opCode) :
		Data(opCode) {
	this->intNum = 0;
}

Num::~Num() {
}

std::string Num::print() const {
	switch (this->opCode) {
	case Opcode::BYTE:
	case Opcode::WORD:
		return std::to_string(this->intNum) + Data::print();
	}
	return "";
}

void Num::parse(Parser &parser, bool allowList, Error *error) {
	switch (this->opCode) {
	case Opcode::BYTE:
		error = NULL;
		this->intNum = parser.readInt(-128, 255, error);
		if (error != NULL)
			return;
		unsigned char arr[1];
		this->dataLength = 1;
		arr[0] = (unsigned char) (intNum & 0xFF);
		this->data = arr;
		break;
	case Opcode::WORD:
		error = NULL;
		this->intNum = parser.readInt(-(2 << 23), (1 << 24) - 1, error);
		if (error != NULL)
			return;
		unsigned char arr1[3];
		this->dataLength = 3;
		arr1[0] = (unsigned char) ((intNum >> 16) & 0xFF);
		arr1[1] = (unsigned char) ((intNum >> 8) & 0xFF);
		arr1[2] = (unsigned char) (intNum & 0xFF);
		this->data = arr1;
		break;
	}
	if (allowList) {
		error = NULL;
		Data::parse(parser, allowList, error);
	}
}
