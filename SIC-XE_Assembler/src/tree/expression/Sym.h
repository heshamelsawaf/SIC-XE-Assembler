/*
 * Sym.h
 *
 *  Created on: 8 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_EXPRESSION_SYM_H_
#define SRC_TREE_EXPRESSION_SYM_H_

#include "Expression.h"

class Sym: public Expression {
public:
	Sym(Location location, std::string value);
	virtual ~Sym();
	std::string print() const;
	int evaluate(Prog &program, Error** error);
private:
	std::string value;
};

#endif /* SRC_TREE_EXPRESSION_SYM_H_ */
