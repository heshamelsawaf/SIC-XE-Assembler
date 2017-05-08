/*
 * DirectivesBase.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_DIRECTIVES_DIRECTIVESBASE_H_
#define SRC_TREE_DIRECTIVES_DIRECTIVESBASE_H_

#include "Directive.h"
#include "../expression/Expression.h"

class DirectivesBase: public Directive {
public:
	DirectivesBase(Location *location, std::string label, Mnemonic *mnemonic,
			Expression *expression);
	virtual ~DirectivesBase();
	std::string printOperand() const;
	int getValue() const;
	void resolve(Prog &program);
	Expression &getExpression() const;

protected:
	Expression *expression;
	int value;
};

#endif /* SRC_TREE_DIRECTIVES_DIRECTIVESBASE_H_ */
