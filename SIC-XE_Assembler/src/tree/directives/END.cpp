/*
 * END.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "END.h"
#include "../Prog.h"

END::END(Location location, std::string label, Mnemonic *mnemonic,
		Expression *expression) :
		DirectivesBase(location, label, mnemonic, expression) {

}

END::~END() {
}

void END::enter(Prog &program, Error** error) {
	program.switchDefault();
	DirectivesBase::enter(program, error);
}

void END::append(Prog &program, Error** error) {
	program.flushAllLiterals();
	DirectivesBase::append(program, error);
}
