/*
 * Literals.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Literals.h"
#include "Prog.h"

Literals::Literals() {
	this->lastPoped = 0;
	this->maxLabelLength = 6;
}

Literals::~Literals() {
	for (unsigned int i = 0; i < this->storage.size(); i++)
		delete storage[i];
	this->storage.clear();
}

std::vector<StorageData> Literals::getStorage() const {
	std::vector<StorageData> sd;
	for (unsigned int i = 0; i < this->storage.size(); i++)
		sd.push_back(*(storage[i]));
	return sd;
}

int Literals::getMaxLabelLength() const {
	return this->maxLabelLength;
}

std::string Literals::printUniqueLabel() const {
	return "*" + std::to_string(this->storage.size());
}

void Literals::append(StorageData *literal) {
	this->storage.push_back(literal);
	if (literal->getLabel().length() > this->maxLabelLength)
		this->maxLabelLength = literal->getLabel().length();
}

StorageData *Literals::find(StorageData &literal) {
	for (int i = this->lastPoped; i < this->storage.size(); i++) {
		StorageData *lit = storage[i];
		if (literal == *(lit))
			return lit;
	}
	return NULL;
}

void Literals::flush(Prog &program) {
	while (lastPoped < storage.size())
		program.append((storage[lastPoped++]));
}

int Literals::getStorageSize() const {
	return storage.size();
}
