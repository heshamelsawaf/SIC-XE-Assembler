/*
 * Symbols.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_SYMBOLS_H_
#define SRC_TREE_SYMBOLS_H_

#include <map>
#include <string>
#include <vector>
#include "Symbol.h"
#include "../asm/Location.h"
#include "../asm/Error.h"

class Symbols {
public:
	Symbols();
	virtual ~Symbols();
	int getMaxSymbolIdentifierLength() const;
	std::string print() const;
	std::vector<Symbol> sortedV() const;
	Symbol *getSymbol(std::string symbolName);
	bool isEvaluated(std::string symbolName);
	void defineLabel(std::string labelName, Location location, int value,
			Error** error);

private:
	int maxSymbolIdentifierLength;
	std::map<std::string, Symbol *> symbolTable;
	bool isDefined(std::string symbolName);
	void define(Symbol *symbol, Error** error);
};

#endif /* SRC_TREE_SYMBOLS_H_ */
