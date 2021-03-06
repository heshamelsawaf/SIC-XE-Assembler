/*
 * Char.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Char.h"
#include "../../parser/Parser.h"

Char::Char(int opCode) :
		Data(opCode) {

}

Char::~Char() {
}

std::string Char::print() const {
	std::string buffer = "C'";
	for (int i = 0; i < data.size(); i++)
		buffer.push_back((unsigned char) data[i]);
	buffer.push_back('\'');
	return buffer + Data::print();
}

void Char::parse(Parser &parser, bool allowList, Error** error) {
	*error = NULL;
	parser.advancePointer('C', error);
	if (*error != NULL)
		return;
	parser.advancePointer('\'', error);
	if (*error != NULL)
		return;
	std::string temp = parser.readUntil('\'');
	data.clear();
	for (std::string::size_type i = 0; i < temp.length(); i++)
		data.push_back((unsigned char) temp[i]);
	if (allowList) {
		*error = NULL;
		Data::parse(parser, allowList, error);
	}
}
