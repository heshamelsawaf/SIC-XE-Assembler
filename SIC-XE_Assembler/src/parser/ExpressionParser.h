/*
 * ExpressionParser.h
 *
 *  Created on: 8 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_PARSER_EXPRESSIONPARSER_H_
#define SRC_PARSER_EXPRESSIONPARSER_H_

#include "../tree/expression/Expression.h"
class Parser;

class ExpressionParser {
public:
	ExpressionParser(Parser *parser);
	virtual ~ExpressionParser();
	Expression *parseExpression(Error *error);

private:
	Parser *parser;
	Expression *readToken(Error *error);
};

#endif /* SRC_PARSER_EXPRESSIONPARSER_H_ */
