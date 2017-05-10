/*
 * Command.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_TREE_COMMAND_H_
#define SRC_TREE_COMMAND_H_

#include <string>
#include <vector>
#include "Node.h"
#include "../asm/Location.h"
#include "../home/Mnemonic.h"

class Command: public Node {
public:
	Command(Location location, std::string label, Mnemonic *mnemonic);
	virtual ~Command();
	virtual std::string print() const;
	virtual void enter(Prog &program, Error** error);
	virtual void append(Prog &program, Error** error);
	bool hasLabel() const;
	std::string getLabel() const;
	void setComment(std::string comment);
	std::string getComment() const;
	virtual std::string printMnemonicName() const;
	virtual Location &getLocation();
	std::string getType() const;
	virtual std::string printOperand() const;
	virtual int getCommandSize() const;
	virtual void burnObjectCode(std::vector<unsigned char>& vec,
			int location) const;
	std::vector<unsigned char> burnObjectCode() const;
	virtual bool burnText(std::string& buffer);

protected:
	std::string type;
	Mnemonic *mnemonic;
	std::string comment;
	Location& location;

private:
	std::string label;
};

#endif /* SRC_TREE_COMMAND_H_ */
