/*
 * Hex.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_DATA_HEX_H_
#define SRC_TREE_DATA_HEX_H_

#include "Data.h"

class Hex: public Data {
public:
	Hex(int opCode);
	virtual ~Hex();
	std::string print() const;
	void parse(Parser &parser, bool allowList, Error** error);
};

#endif /* SRC_TREE_DATA_HEX_H_ */
