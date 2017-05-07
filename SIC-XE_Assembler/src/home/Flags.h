/*
 * Flags.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_HOME_FLAGS_H_
#define SRC_HOME_FLAGS_H_

#include <string>

class Flags {
public:
	Flags();
	virtual ~Flags();
	std::string print() const;
	std::string printOperand(std::string operand) const;
	unsigned char combineWithOpCode(int opCode) const;
	int get_X() const;
	bool isIndexed() const;
	void setIndexed();
	int getMinOperand() const;
	int getMaxOperand() const;
	const int INDEXED = 0x80;

private:
	int rightMostTwoDigits;
	int x;
};

#endif /* SRC_HOME_FLAGS_H_ */
