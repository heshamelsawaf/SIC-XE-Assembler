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
	Mnemonic(const std::string name, const int opCode);
	virtual ~Mnemonic();
	const std::string getName(void) const;
private:
	const std::string name;
	const int opCode;
};

#endif /* SRC_HOME_MNEMONIC_H_ */
