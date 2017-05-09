/*
 * StorageData.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "StorageData.h"

StorageData::StorageData(Location location, std::string label,
		Mnemonic *mnemonic, Data *data, bool isLiteral) :
		Directive(location, label, mnemonic) {
	this->data = data;
	this->isLiteral = isLiteral;
}

StorageData::StorageData(Location location, std::string label,
		Mnemonic *mnemonic, Data *data) :
		Directive(location, label, mnemonic) {
	this->data = data;
	this->isLiteral = false;
}

StorageData::~StorageData() {
	delete this->data;
}

bool StorageData::operator ==(const StorageData &storageData) const {
	return this->data == storageData.getData();
}

Data *StorageData::getData() const {
	return this->data;
}

std::string StorageData::printMnemonicName() const {
	return (isLiteral ? "=" : "") + mnemonic->getName();
}

std::string StorageData::printOperand() const {
	return this->data->print();
}

int StorageData::getCommandSize() const {
	return this->data->getSize();
}

void StorageData::burnObjectCode(unsigned char *dta, int location,
		int length) const {
	this->data->burnObjectCode(dta, location, length);
}

