/*
 * Buffer.cpp
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#include "Buffer.h"

Buffer::Buffer() {
	this->buffer = "";
	this->position = 0;
	this->row = 1;
	this->column = 1;
	this->previousCharacter = '\0';

}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}

void Buffer::init(const std::string buffer) {
	this->buffer = buffer;
	this->position = 0;
	this->row = 1;
	this->column = 1;
}

int Buffer::getPosition() const {
	return this->position;
}
int Buffer::getRow() const {
	return this->row;
}
int Buffer::getColumn() const {
	return this->column;
}

Location *Buffer::getLocation() const {
	return new Location(this->position, this->row, this->column);
}

std::string Buffer::subString(int start, int end) const {
	return this->buffer.substr(start, end - start);
}

std::string Buffer::subString(int start) const {
	return this->subString(start, this->position);
}

int Buffer::availableCount() const {
	return this->buffer.length() - this->position;
}

bool Buffer::isReady(int position) const {
	return (unsigned int) this->position < this->buffer.length();
}

bool Buffer::isReady() const {
	return this->isReady(this->position);
}

char Buffer::getPeekCharacter(int front) const {
	if (this->availableCount() <= front)
		return '\0';
	return this->buffer[this->position + front];
}

char Buffer::getPeekCharacter() const {
	return this->getPeekCharacter(0);
}

char Buffer::advancePointer() {
	this->previousCharacter = this->getPeekCharacter();
	++position;
	switch (this->previousCharacter) {
	case '\n':
		++row;
		++column = 1;
		break;
	case '\t':
		column = ((column - 1) / 4) * 4 + 5;
		break;
	default:
		++column;
	}
	return this->previousCharacter;
}

int Buffer::advancePointer(int count) {
	int temp = 0;
	while (this->isReady() && temp++ < count)
		this->advancePointer();
	return temp;
}

void Buffer::advancePointer(char character, Error *error) {
	if (this->advancePointerIf(character)) {
		error = NULL;
		return;
	}
	std::string err = "Expected ";
	err.push_back(character);
	error = new Error(this->getLocation(), err + "!");
}

bool Buffer::advancePointerIf(char character) {
	if (this->getPeekCharacter() != character)
		return false;
	this->advancePointer();
	return true;
}

bool Buffer::advancePointerIf(std::string str) {
	for (unsigned int i = 0; i < str.length(); i++)
		if (this->getPeekCharacter(i) != str[i])
			return false;
	this->advancePointer(str.length());
	return true;
}

void Buffer::advancePointerUntil(char delimiter) {
	while (this->isReady() && this->getPeekCharacter() != delimiter)
		this->advancePointer();
	this->advancePointer();
}

std::string Buffer::readUntil(char delimiter) {
	int mark = this->position;
	this->advancePointerUntil(delimiter);
	return this->subString(mark, position - 1);
}
