/*
 * OperandParser.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_PARSER_OPERANDPARSER_H_
#define SRC_PARSER_OPERANDPARSER_H_

#include "../tree/storage/StorageData.h"
#include "../tree/Command.h"
#include "../tree/data/Data.h"
#include "../asm/Location.h"
#include "../home/Mnemonic.h"
#include "../asm/Error.h"
#include <string>

class OperandParser {
public:
	OperandParser(Parser *parser);
	virtual ~OperandParser();
	Data *parseData(int opcode, bool allowList, Error *error);
	Command *parse(Location *location, std::string label, Mnemonic *mnemonic,
			Error *error);

private:
	Parser* parser;
	void checkWhitespace(std::string name, Error *error);
	Mnemonic *parseLiteralSpec();
	StorageData *parseLiteralData(Error *error);
	Command *parseF3(Location *location, std::string label, Mnemonic *mnemonic,
			Error *error);
	Command *parseF3Extended(Location *location, std::string label,
			Mnemonic *mnemonic, Error *error);
	Command *parseDe(Location *location, std::string label, Mnemonic *mnemonic,
			Error *error);
	Command *parseSe(Location *location, std::string label, Mnemonic *mnemonic,
			Error *error);
	Command *parseSd(Location *location, std::string label, Mnemonic *mnemonic,
			Error *error);
	Command *parseSd_(Location *location, std::string label, Mnemonic *mnemonic,
			Error *error);
};

#endif /* SRC_PARSER_OPERANDPARSER_H_ */
