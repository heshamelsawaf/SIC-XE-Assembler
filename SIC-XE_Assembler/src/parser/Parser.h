/*
 * Parser.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include "BufferDecorator.h"
#include "../asm/ErrorController.h"
#include "../home/Mnemonics.h"
#include "OperandParser.h"
#include "ExpressionParser.h"
#include "../asm/Error.h"
#include <string>

class Parser: public BufferDecorator {
public:
	Parser(Mnemonics *mnemonics, ErrorController *errorController);
	virtual ~Parser();
	void checkWhitespace(std::string fmt, Error *error);
	Command *parseIfCommand(Error *error);
	OperandParser &getOperandParser() const;
	ExpressionParser &getExpressionParser() const;
	Mnemonics &getMnemonics() const;
	Prog &getProgram() const;
	Prog *parseProgram();

private:
	OperandParser *operandParser;
	Mnemonics *mnemonics;
	ErrorController *errorController;
	ExpressionParser *expressionParser;
	Prog *program;
};

#endif /* SRC_PARSER_PARSER_H_ */
