/*
 * START.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "START.h"

START::START(Location location, std::string label, Mnemonic *mnemonic,
		Expression *expression) :
		DirectivesBase(location, label, mnemonic, expression) {

}

START::~START() {
	// TODO Auto-generated destructor stub
}

void START::append(Prog &program, Error** error) {
	*error = NULL;
	DirectivesBase::append(program, error);
}
