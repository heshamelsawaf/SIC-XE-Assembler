/*
 * START.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_DIRECTIVES_START_H_
#define SRC_TREE_DIRECTIVES_START_H_

#include "DirectivesBase.h"

class START: public DirectivesBase {
public:
	START(Location location, std::string label, Mnemonic *mnemonic,
			Expression *expression);
	virtual ~START();
	void append(Prog &program, Error** error);
};

#endif /* SRC_TREE_DIRECTIVES_START_H_ */
