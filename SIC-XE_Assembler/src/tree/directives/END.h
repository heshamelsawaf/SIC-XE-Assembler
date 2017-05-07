/*
 * END.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_DIRECTIVES_END_H_
#define SRC_TREE_DIRECTIVES_END_H_

#include "DirectivesBase.h"

class END: public DirectivesBase {
public:
	END(Location *location, std::string label, Mnemonic *mnemonic);
	virtual ~END();
	void enter(Prog &program, Error *error);
	void append(Prog &program, Error *error);
};

#endif /* SRC_TREE_DIRECTIVES_END_H_ */
