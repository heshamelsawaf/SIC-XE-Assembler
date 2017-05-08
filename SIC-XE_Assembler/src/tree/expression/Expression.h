/*
 * Expression.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_EXPRESSION_EXPRESSION_H_
#define SRC_TREE_EXPRESSION_EXPRESSION_H_

#include "../../asm/Location.h"
#include "../../asm/Error.h"
#include <string>

class Prog;

class Expression {
public:
	Expression(std::string name, Location *location);
	virtual ~Expression();
	virtual std::string print() const;
	Expression *getParsedExpression();
	virtual int evaluate(Prog &program, Error *error);

protected:
	std::string name;
	Location *location;

};

#endif /* SRC_TREE_EXPRESSION_EXPRESSION_H_ */
