/*
 * RES.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_STORAGE_RES_H_
#define SRC_TREE_STORAGE_RES_H_

#include "../expression/Expression.h"
#include "Storage.h"

class RES: public Storage {
public:
	RES(Location location, std::string label, Mnemonic *mnemonic,
			Expression *expression);
	virtual ~RES();
	std::string printOperand() const;
	int getCommandSize() const;
	void resolve(Prog &program, Error** error);
	void burnObjectCode(std::vector<unsigned char>& vec, int location) const;

private:
	int count;
	Expression *expression;
};

#endif /* SRC_TREE_STORAGE_RES_H_ */
