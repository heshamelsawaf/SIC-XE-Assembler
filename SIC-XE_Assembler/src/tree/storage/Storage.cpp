/*
 * Storage.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Storage.h"

Storage::Storage(Location *location, std::string label, Mnemonic *mnemonic) :
		Command(location, label, mnemonic) {
	this->type = "Storage";
	this->dataLength = 0;
}

Storage::~Storage() {
}

void Storage::burnObjectCode(unsigned char *data, int location,
		int length) const {

}

int Storage::getDataLength() const {
	return this->dataLength;
}
