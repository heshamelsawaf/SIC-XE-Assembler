/*
 * Directive.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_DIRECTIVES_DIRECTIVE_H_
#define SRC_TREE_DIRECTIVES_DIRECTIVE_H_

#include "../../home/Mnemonic.h"
#include "../../asm/Location.h"
#include "../Command.h"
#include <string>

class Directive: public Command {
public:
	Directive(Location location, std::string label, Mnemonic *mnemonic);
	virtual ~Directive();
	virtual std::string printOperand() const;
	virtual int getCommandSize() const;
	virtual void burnObjectCode(std::vector<unsigned char>& vec,
			int location) const;
};

#endif /* SRC_TREE_DIRECTIVES_DIRECTIVE_H_ */
