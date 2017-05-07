/*
 * Char.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_DATA_CHAR_H_
#define SRC_TREE_DATA_CHAR_H_

#include "Data.h"

class Char: public Data {
public:
	Char(int opCode);
	virtual ~Char();
	std::string print() const;
	void parse(Parser &parser, bool allowList, Error *error);
};

#endif /* SRC_TREE_DATA_CHAR_H_ */
