/*
 * Comment.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_COMMENT_H_
#define SRC_TREE_COMMENT_H_

#include "Command.h"
#include "../asm/Location.h"
#include <string>

class Comment: public Command {
public:
	Comment(Location location, std::string comment);
	virtual ~Comment();
	std::string print() const;
	std::string printOperand() const;
	int getCommandSize() const;
	void burnObjectCode(unsigned char *data, int location, int length) const;
};

#endif /* SRC_TREE_COMMENT_H_ */
