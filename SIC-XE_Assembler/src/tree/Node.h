/*
 * Node.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_NODE_H_
#define SRC_TREE_NODE_H_

#include "../asm/Error.h"

class Prog;

class Node {
public:
	Node();
	virtual ~Node();
	virtual void enter(Prog &program, Error** error);
	virtual void leave(Prog &program, Error** error);
};

#endif /* SRC_TREE_NODE_H_ */
