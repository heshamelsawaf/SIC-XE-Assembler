/*
 * Sym.cpp
 *
 *  Created on: 8 May 2017
 *      Author: heshamelsawaf
 */

#include "Sym.h"
#include "../Prog.h"

Sym::Sym(Location *location, std::string value) :
		Expression("<sym>", location) {
	this->value = value;
}

Sym::~Sym() {
}

std::string Sym::print() const {
	return value;
}

int Sym::evaluate(Prog &program, Error *error) {
	if (program.getCurrentSection().getSymbols().isEvaluated(value))
		return program.getCurrentSection().getSymbols().getSymbol(value)->getValue();
	error = new Error(location->clone(), "Undefined symbol '" + value + "'!");
	return 0;
}
