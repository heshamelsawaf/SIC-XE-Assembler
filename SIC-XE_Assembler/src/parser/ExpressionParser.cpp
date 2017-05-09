/*
 * ExpressionParser.cpp
 *
 *  Created on: 8 May 2017
 *      Author: heshamelsawaf
 */

#include "ExpressionParser.h"
#include "Parser.h"
#include "../tree/expression/Int.h"
#include "../tree/expression/Sym.h"
#include "../SIC.h"

ExpressionParser::ExpressionParser(Parser *parser) :
		parser(parser) {

}

ExpressionParser::~ExpressionParser() {
}

Expression *ExpressionParser::readToken(Error** error) {
	parser->skipWhitespace();
	Location loc = parser->getLocation();
	if (std::isdigit(parser->getPeekCharacter())) {
		*error = NULL;
		int te = parser->readInt(0, SIC::MAX_SICADDR, error);
		if (*error != NULL) {
			return NULL;
		}
		return new Int(loc, te);
	}
	if (std::isalpha(parser->getPeekCharacter())) {
		*error = NULL;
		std::string te = parser->readSymbol(error);
		if (*error != NULL) {
			return NULL;
		}
		return new Sym(loc, te);
	}
	return NULL;
}

Expression *ExpressionParser::parseExpression(Error** error) {
	*error = NULL;
	Expression *ts = this->readToken(error);
	if (*error != NULL)
		return NULL;
	return ts;
}
