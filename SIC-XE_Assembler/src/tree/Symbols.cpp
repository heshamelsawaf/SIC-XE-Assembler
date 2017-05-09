/*
 * Symbols.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "Symbols.h"
#include <algorithm>

Symbols::Symbols() {
	this->maxSymbolIdentifierLength = 6;
}

Symbols::~Symbols() {
	for (std::map<std::string, Symbol *>::const_iterator i =
			this->symbolTable.begin(); i != this->symbolTable.end(); i++)
		delete i->second;
	this->symbolTable.clear();
}

int Symbols::getMaxSymbolIdentifierLength() const {
	return this->maxSymbolIdentifierLength;
}

std::string Symbols::print() const {
	std::string buffer = "";
	for (std::map<std::string, Symbol *>::const_iterator i =
			this->symbolTable.begin(); i != this->symbolTable.end(); i++) {
		buffer += i->second->print();
		buffer += ", ";
	}
	return buffer;
}

std::vector<Symbol> Symbols::sortedV() const {
	std::vector<Symbol> syms;
	for (std::map<std::string, Symbol *>::const_iterator i =
			this->symbolTable.begin(); i != this->symbolTable.end(); i++)
		syms.push_back(*(i->second));
	std::sort(syms.begin(), syms.end());
	return syms;
}

Symbol *Symbols::getSymbol(std::string symbolName) {
	return symbolTable[symbolName];
}

bool Symbols::isDefined(std::string symbolName) {
	return (this->symbolTable.find(symbolName) != this->symbolTable.end());
}

bool Symbols::isEvaluated(std::string symbolName) {
	return this->isDefined(symbolName)
			&& this->getSymbol(symbolName)->isEvaluated();
}

void Symbols::define(Symbol *symbol, Error** error) {
	if (!(symbol->getSymbolName().compare(""))) {
		delete symbol;
		*error = NULL;
		return;
	}
	if (this->isDefined(symbol->getSymbolName())) {
		delete symbol;
		std::string errMsg = "Duplicate symbol '" + symbol->getSymbolName()
				+ "'!";
		*error = new Error(symbol->getSymbolLocation(), errMsg);
		return;
	}
	if ((int) symbol->getSymbolName().length()
			> this->maxSymbolIdentifierLength)
		this->maxSymbolIdentifierLength = symbol->getSymbolName().length();
	symbolTable[symbol->getSymbolName()] = symbol;
	*error = NULL;
}

void Symbols::defineLabel(std::string labelName, Location location, int value,
		Error** error) {
	*error = NULL;
	this->define(new Symbol(labelName, location, value), error);
}

