/*
 * Literals.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_LITERALS_H_
#define SRC_TREE_LITERALS_H_

#include "../asm/Error.h"
#include "storage/StorageData.h"
#include <vector>

class Prog;

class Literals {
public:
	Literals();
	virtual ~Literals();
	std::vector<StorageData> getStorage() const;
	int getStorageSize() const;
	int getMaxLabelLength() const;
	std::string printUniqueLabel() const;
	void append(StorageData *literal);
	StorageData *find(StorageData &literal);
	void flush(Prog &program);

private:
	std::vector<StorageData *> storage;
	int lastPoped;
	int maxLabelLength;
};

#endif /* SRC_TREE_LITERALS_H_ */
