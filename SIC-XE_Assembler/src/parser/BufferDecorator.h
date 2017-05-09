/*
 * BufferDecorator.h
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_PARSER_INPUTDECORATOR_H_
#define SRC_PARSER_INPUTDECORATOR_H_

#include "Buffer.h"
#include "../asm/Error.h"
#include <string>

class BufferDecorator: public Buffer {
public:
	BufferDecorator();
	virtual ~BufferDecorator();
	void skipWhitespace();
	std::string readIfComment(bool requireDot, bool skipEmptyLines);
	std::string readIfLabel();
	std::string readIfMnemonic();
	void skipComma(Error** error);
	bool skipIfComma();
	bool skipIfIndexed(Error** error);
	std::string readSymbol(Error** error);
	int readInt(int low, int high, Error** error);

private:
	bool isWhitespace() const;
	bool isAlpha() const;
	bool isAlphanumeric() const;
	void skipAlphanumeric();
	std::string readAlphanumeric();
	std::string readDigits(int radix);

};

#endif /* SRC_PARSER_INPUTDECORATOR_H_ */
