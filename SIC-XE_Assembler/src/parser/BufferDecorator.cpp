/*
 * BufferDecorator.cpp
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#include "BufferDecorator.h"
#include <cctype>
#include <exception>
#include <sstream>

BufferDecorator::BufferDecorator() {
	// TODO Auto-generated constructor stub

}

BufferDecorator::~BufferDecorator() {
	// TODO Auto-generated destructor stub
}

bool BufferDecorator::isWhitespace() const {
	return this->getPeekCharacter() == ' ' || this->getPeekCharacter() == '\t'
			|| this->getPeekCharacter() == '\r';
}

bool BufferDecorator::isAlpha() const {
	return std::isalpha(this->getPeekCharacter())
			|| this->getPeekCharacter() == '_';
}

bool BufferDecorator::isAlphanumeric() const {
	return std::isalnum(this->getPeekCharacter())
			|| this->getPeekCharacter() == '_';
}

void BufferDecorator::skipWhitespace() {
	while (this->isWhitespace())
		this->advancePointer();
}

void BufferDecorator::skipAlphanumeric() {
	while (this->isAlphanumeric())
		this->advancePointer();
}

std::string BufferDecorator::readAlphanumeric() {
	int mark = this->position;
	this->skipAlphanumeric();
	return this->subString(mark);
}

std::string BufferDecorator::readDigits(int radix) {
	int mark = this->position;
	bool temp = true;
	while (true) {
		char c = this->getPeekCharacter();
		switch (radix) {
		case 2:
			temp = (c == '0' || c == '1' ? true : false);
			break;
		case 8:
			temp = (c - '0' < 8 && c - '0' >= 0 ? true : false);
			break;
		case 10:
			temp = (c - '0' < 10 && c - '0' >= 0 ? true : false);
			break;
		case 16:
			temp = ((c - '0' < 10 && c - '0' >= 0)
					|| (c - 'a' < 6 && c - 'a' >= 0)
					|| (c - 'A' < 6 && c - 'A' >= 0) ? true : false);
			break;
		default:
			temp = false;
		}
		if (!temp)
			break;
		this->advancePointer();
	}
	return this->subString(mark);
}

std::string BufferDecorator::readIfComment(bool requireDot,
		bool skipEmptyLines) {
	bool hasDot = this->advancePointerIf('.');
	if ((requireDot || this->column == 1) && !hasDot)
		return "";
	std::string comment = this->readUntil('\n');
	size_t first = comment.find_first_not_of(' ');
	if (std::string::npos != first) {
		size_t last = comment.find_last_not_of(' ');
		comment = comment.substr(first, (last - first + 1));

	}
	if (skipEmptyLines && comment.length() == 0)
		return "";
	return comment;
}

std::string BufferDecorator::readIfLabel() {
	if (this->column == 1 && this->isAlpha())
		return this->readAlphanumeric();
	return "";
}

std::string BufferDecorator::readIfMnemonic() {
	int mark = this->position;
	this->advancePointerIf('+');
	this->skipAlphanumeric();
	if (mark == this->position)
		return "";
	return this->subString(mark);
}

void BufferDecorator::skipComma(Error *error) {
	this->skipWhitespace();
	this->advancePointer(',', error);
	this->skipWhitespace();
}

bool BufferDecorator::skipIfComma() {
	this->skipWhitespace();
	bool res = this->advancePointerIf(',');
	this->skipWhitespace();
	return res;
}

bool BufferDecorator::skipIfIndexed(Error *error) {
	if (this->skipIfComma()) {
		this->advancePointer('X', error);
		return true;
	}
	return false;
}

std::string BufferDecorator::readSymbol(Error *error) {
	std::string sym = this->readAlphanumeric();
	if (sym.length() > 0) {
		error = NULL;
		return sym;
	}
	error = new Error(this->getLocation(), "Symbol expected");
	return "";
}

int BufferDecorator::readInt(int low, int high, Error *error) {
	// first detect radix
	int radix = -1;
	bool negative = this->advancePointerIf('-');
	if (this->getPeekCharacter() == '0') {
		// 0bBIN, 0oOCT, 0xHEX
		switch (this->getPeekCharacter(1)) {
		case 'b':
			radix = 2;
			break;
		case 'o':
			radix = 8;
			break;
		case 'x':
			radix = 16;
			break;
		}
		// we got radix != 10
		if (radix != -1) {
			this->advancePointer();
			this->advancePointer();
		} else
			radix = 10;
	} else if (std::isdigit(this->getPeekCharacter()))
		radix = 10;
	else {
		error = new Error(this->getLocation(), "Number expected");
		return 0;
	}
	// read digits
	int num;
	try {
		num = std::stoi(this->readDigits(radix), nullptr, radix);
	} catch (std::exception &e) {
		error = new Error(this->getLocation(), "Invalid number");
		return 0;
	}
	// number must not be followed by letter or digit
	if (std::isdigit(this->getPeekCharacter())
			|| std::isalpha(this->getPeekCharacter())) {
		std::string err = "invalid digit";
		err.push_back(this->getPeekCharacter());
		error = new Error(this->getLocation(), err);
		return 0;
	}
	// check range
	if (negative)
		num = -num;
	if (num < low || num > high) {
		std::stringstream buffer;
		buffer << "Number '" << num << "' out of range [" << low << ".." << high
				<< "]";
		error = new Error(this->getLocation(), buffer.str());
		return 0;
	}
	error = NULL;
	return num;
}
