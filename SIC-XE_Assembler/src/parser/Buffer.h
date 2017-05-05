/*
 * Buffer.h
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_PARSER_BUFFER_H_
#define SRC_PARSER_BUFFER_H_

#include <string>
#include "../asm/Location.h"
#include "../asm/Error.h"

class Buffer {
public:
	Buffer();
	virtual ~Buffer();
	void init(const std::string buffer);
	int getPosition() const;
	int getRow() const;
	int getColumn() const;
	Location *getLocation() const;
	bool isReady() const;
	char getPeekCharacter() const;
	void advancePointer(char character, Error *error);
	bool advancePointerIf(char character);
	bool advancePointerIf(std::string str);
	void advancePointerUntil(char delimiter);
	std::string readUntil(char delimiter);

private:
	std::string subString(int start, int end) const;
	int availableCount() const;
	bool isReady(int position) const;
	int advancePointer(int count);

protected:
	std::string buffer;
	int position;
	int row;
	int column;
	char previousCharacter;
	std::string subString(int start) const;
	char getPeekCharacter(int front) const;
	char advancePointer();
};

#endif /* SRC_PARSER_BUFFER_H_ */
