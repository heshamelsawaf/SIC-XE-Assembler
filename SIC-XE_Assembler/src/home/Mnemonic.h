/*
 * Mnemonic.h
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_HOME_MNEMONIC_H_
#define SRC_HOME_MNEMONIC_H_

#include <string>

class Mnemonic {
public:
	Mnemonic(std::string name, int opCode, int type);
	virtual ~Mnemonic();
	std::string getName() const;
	int getType() const;
	int getOpCode() const;
private:
	std::string name;
	int type;
	int opCode;
};

#endif /* SRC_HOME_MNEMONIC_H_ */
