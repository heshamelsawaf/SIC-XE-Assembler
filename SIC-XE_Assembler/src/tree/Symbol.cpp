/*
 * Symbol.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Symbol.h"

Symbol::Symbol(std::string symbolName, Location location, int value) :
		location(location) {
	this->symbolName = symbolName;
	this->value = value;
	this->evaluated = true;
	this->absolute = false;
}

Symbol::~Symbol() {
	// TODO Auto-generated destructor stub
}

int Symbol::Compare(const Symbol &symbol) const {
	return (this->symbolName < symbol.getSymbolName() ? -1 :
			this->symbolName == symbol.getSymbolName() ? 0 : 1);
}

bool Symbol::operator ==(const Symbol &symbol) const {
	return !(this->Compare(symbol));
}

bool Symbol::operator <(const Symbol &symbol) const {
	return this->Compare(symbol) < 0;
}

std::string Symbol::print() const {
	return this->symbolName + "=" + this->printValue();
}

std::string Symbol::printType() const {
	if (absolute)
		return "absolute";
	return "relative";
}

std::string Symbol::printValue() const {
	return this->evaluated ? std::to_string(this->value) : "?";
}

std::string Symbol::printExpression() const {
	return "label";
}

bool Symbol::isAbsolute() const {
	return this - absolute;
}

void Symbol::setAbsolute(bool absolute) {
	this->absolute = absolute;
}

int Symbol::getValue() const {
	return this->value;
}

bool Symbol::isEvaluated() const {
	return this->evaluated;
}

void Symbol::eval(Prog &program, Error** error) {
	evaluated = true;
	*error = NULL;
}

std::string Symbol::getSymbolName() const {
	return this->symbolName;
}

Location &Symbol::getSymbolLocation() {
	return location;
}
