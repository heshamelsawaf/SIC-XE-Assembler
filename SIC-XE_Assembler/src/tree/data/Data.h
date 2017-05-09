/*
 * Data.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_DATA_DATA_H_
#define SRC_TREE_DATA_DATA_H_

#include <string>
#include <vector>
#include "../../asm/Error.h"

class Parser;

class Data {
public:
	Data(int opcode);
	virtual ~Data();
	virtual std::string print() const;
	virtual void parse(Parser &parser, bool allowList, Error** error);
	bool operator ==(const Data &dta) const;
	int getSize() const;
	int getOpCode() const;
	const std::vector<unsigned char>& getData() const;
	Data *getNext() const;
	void burnObjectCode(std::vector<unsigned char>& vec, int location) const;

private:
	int sizes() const;

protected:
	int opCode;
	std::vector<unsigned char> data;
	Data *next;
};

#endif /* SRC_TREE_DATA_DATA_H_ */
