/*
 * Num.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_DATA_NUM_H_
#define SRC_TREE_DATA_NUM_H_

#include "Data.h"

class Num: public Data {
public:
	Num(int opCode);
	virtual ~Num();
	std::string print() const;
	void parse(Parser &parser, bool allowList, Error *error);

private:
	int intNum;
};

#endif /* SRC_TREE_DATA_NUM_H_ */
