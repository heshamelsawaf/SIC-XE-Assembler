/*
 * RES.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_STORAGE_RES_H_
#define SRC_TREE_STORAGE_RES_H_

#include "Storage.h"

class RES: public Storage {
public:
	RES(Location *loaction, std::string label, Mnemonic *mnemonic);
	virtual ~RES();
	std::string printOperand() const;
	int getCommandSize() const;
	void resolve(Prog &program, Error *error);
	void burnObjectCode(unsigned char *data, int location, int length) const;

private:
	int count;
};

#endif /* SRC_TREE_STORAGE_RES_H_ */
