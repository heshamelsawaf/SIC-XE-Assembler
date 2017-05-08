/*
 * Int.h
 *
 *  Created on: 8 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_EXPRESSION_INT_H_
#define SRC_TREE_EXPRESSION_INT_H_

#include "Expression.h"

class Int: public Expression {
public:
	Int(Location *location, int value);
	virtual ~Int();
	std::string print() const;
	int evaluate(Prog &program, Error *error);
private:
	int value;
};

#endif /* SRC_TREE_EXPRESSION_INT_H_ */
