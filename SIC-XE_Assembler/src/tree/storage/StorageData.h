/*
 * StorageData.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_STORAGE_STORAGEDATA_H_
#define SRC_TREE_STORAGE_STORAGEDATA_H_

#include "../../home/Mnemonic.h"
#include "../../asm/Location.h"
#include "../directives/Directive.h"
#include "../data/Data.h"
#include <string>

class StorageData: public Directive {
public:
	StorageData(Location location, std::string label, Mnemonic *mnemonic,
			Data *data, bool isLiteral);
	StorageData(Location location, std::string label, Mnemonic *mnemonic,
			Data *data);
	virtual ~StorageData();
	bool operator ==(const StorageData &storageData) const;
	std::string printMnemonicName() const;
	std::string printOperand() const;
	int getCommandSize() const;
	void burnObjectCode(std::vector<unsigned char>& vec, int location) const;
	Data *getData() const;

private:
	Data *data;
	bool isLiteral;

};

#endif /* SRC_TREE_STORAGE_STORAGEDATA_H_ */
