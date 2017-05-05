/*
 * Mnemonics.h
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_HOME_MNEMONICS_H_
#define SRC_HOME_MNEMONICS_H_

#include <map>
#include <string>
#include "Mnemonic.h"

class Mnemonics {
public:
	Mnemonics();
	virtual ~Mnemonics();
	std::map<std::string, Mnemonic*> initMnemonics(void);
private:
	const std::map<std::string, Mnemonic*> mnemonicsMap;
};

#endif /* SRC_HOME_MNEMONICS_H_ */
