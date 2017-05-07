/*
 * Relocation.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_RELOCATION_H_
#define SRC_TREE_RELOCATION_H_

class Relocation {
public:
	Relocation(int address, int length);
	virtual ~Relocation();
};

#endif /* SRC_TREE_RELOCATION_H_ */
