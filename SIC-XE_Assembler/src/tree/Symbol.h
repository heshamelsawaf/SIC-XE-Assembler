/*
 * Symbol.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_SYMBOL_H_
#define SRC_TREE_SYMBOL_H_

#include "../asm/Location.h"
#include "Node.h"
#include <string>

class Symbol: public Node {
public:
	Symbol(std::string symbolName, Location *location, int value);
	virtual ~Symbol();
	int Compare(const Symbol &symbol) const;
	bool operator ==(const Symbol &symbol) const;
	bool operator <(const Symbol &symbol) const;
	std::string print() const;
	std::string printType() const;
	std::string printExpression() const;
	bool isAbsolute() const;
	void setAbsolute(bool absolute);
	int getValue() const;
	bool isEvaluated() const;
	void eval(Prog &program, Error *error);
	std::string getSymbolName() const;
	Location &getSymbolLocation() const;

private:
	std::string symbolName;
	Location *location;
	bool absolute;
	bool evaluated;
	int value;
	std::string printValue() const;

};

#endif /* SRC_TREE_SYMBOL_H_ */
