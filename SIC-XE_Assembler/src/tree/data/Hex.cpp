/*
 * Hex.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Hex.h"
#include "../../Conversion.h"
#include "../../parser/Parser.h"

Hex::Hex(int opCode) :
		Data(opCode) {

}

Hex::~Hex() {
}

std::string Hex::print() const {
	std::string buffer = "X'"
			+ Conversion::bytesToHex(this->data, 0, this->dataLength,
					this->dataLength);
	buffer.push_back('\'');
	return buffer + Data::print();
}

void Hex::parse(Parser &parser, bool allowList, Error *error) {
	error = NULL;
	parser.advancePointer('X', error);
	if (error != NULL)
		return;
	parser.advancePointer('\'', error);
	if (error != NULL)
		return;
	std::string temp = parser.readUntil('\'');
	if (temp.length() % 2) {
		std::string errMsg = "Invalid length of hex encoding '" + temp + "'!";
		error = new Error(parser.getLocation()->clone(), errMsg);
		return;
	}
	Conversion::hexToBytes(temp, this->data);
	this->dataLength = temp.length() / 2;
	if (allowList) {
		error = NULL;
		Data::parse(parser, allowList, error);
	}
}
