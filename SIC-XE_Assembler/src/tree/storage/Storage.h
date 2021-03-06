/*
 * Storage.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_STORAGE_STORAGE_H_
#define SRC_TREE_STORAGE_STORAGE_H_

#include "../Command.h"

class Storage: public Command {
public:
	Storage(Location location, std::string label, Mnemonic *mnemonic);
	virtual ~Storage();
	virtual void burnObjectCode(std::vector<unsigned char>& vec,
			int location) const;
};

#endif /* SRC_TREE_STORAGE_STORAGE_H_ */
