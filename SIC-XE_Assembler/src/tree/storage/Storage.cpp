/*
 * Storage.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Storage.h"

Storage::Storage(Location location, std::string label, Mnemonic *mnemonic) :
		Command(location, label, mnemonic) {
	this->type = "Storage";
}

Storage::~Storage() {
}

void Storage::burnObjectCode(std::vector<unsigned char>& vec,
		int location) const {

}
