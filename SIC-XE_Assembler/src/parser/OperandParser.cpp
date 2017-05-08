/*
 * OperandParser.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "OperandParser.h"
#include "Parser.h"
#include "../home/Opcode.h"
#include "../tree/storage/StorageData.h"
#include "../tree/storage/RES.h"
#include "../tree/data/Char.h"
#include "../tree/data/Hex.h"
#include "../tree/data/Num.h"
#include "../tree/Prog.h"
#include "../tree/directives/START.h"
#include "../tree/directives/END.h"
#include "../tree/instructions/InstructionFormat3.h"
#include "../tree/instructions/LiteralInstruction.h"
#include "../tree/instructions/InstructionFormat3Abstract.h"
#include "../tree/instructions/InstructionFormat3Extended.h"

OperandParser::OperandParser(Parser *parser) {
	this->parser = parser;
}

OperandParser::~OperandParser() {
}

void OperandParser::checkWhitespace(std::string name, Error *error) {
	this->parser->checkWhitespace(
			"Missing whitespace after mnemonic '" + name + "'!", error);
}

Data *OperandParser::parseData(int opcode, bool allowList, Error *error) {
	Data *data;
	switch (this->parser->getPeekCharacter()) {
	case 'C':
		data = new Char(opcode);
		break;
	case 'X':
		data = new Hex(opcode);
		break;
	default:
		data = new Num(opcode);
		break;
	}
	error = NULL;
	data->parse(*parser, allowList, error);
	if (error != NULL) {
		delete data;
		return NULL;
	}
	return data;
}

Mnemonic *OperandParser::parseLiteralSpec() {
	Mnemonic *mnm;
	// WORD, or BYTE (default) literal
	if (this->parser->advancePointerIf("BYTE")
			|| this->parser->advancePointerIf("B"))
		mnm = this->parser->getMnemonics().get("BYTE");
	else {
		mnm = this->parser->getMnemonics().get("WORD");
		this->parser->advancePointerIf("WOED");
		this->parser->advancePointerIf("W");
	}
	return mnm;
}

StorageData *OperandParser::parseLiteralData(Error *error) {
	Location *location = this->parser->getLocation();
	Mnemonic *mnm = this->parseLiteralSpec();
	this->parser->skipWhitespace();
	error = NULL;
	Data *data = this->parseData(mnm->getOpCode(), false, error);
	if (error != NULL)
		return NULL;
	std::string lbl =
			this->parser->getProgram().getCurrentSection().getLiterals().printUniqueLabel();
	return new StorageData(location, lbl, mnm, data);
}

Command *OperandParser::parseF3(Location *location, std::string label,
		Mnemonic *mnemonic, Error *error) {
	return new InstructionFormat3(location, label, mnemonic);
}

Command *OperandParser::parseF3Extended(Location *location, std::string label,
		Mnemonic *mnemonic, Error *error) {
	error = NULL;
	this->checkWhitespace(mnemonic->getName(), error);
	if (error != NULL)
		return NULL;
	Flags *flags = new Flags();
	int operand;
	std::string symbol;
	// check if literal
	if (this->parser->advancePointerIf('=')) {
		InstructionFormat3Abstract *cmd = new InstructionFormat3Extended(
				location, label, mnemonic, flags, 0, "");
		error = NULL;
		StorageData *lit = this->parseLiteralData(error);
		if (error != NULL) {
			delete cmd;
			cmd = NULL;
			return NULL;
		}
		return new LiteralInstruction(cmd, lit);
	}
	// read operand: number, symbol, '*'
	if (std::isdigit(this->parser->getPeekCharacter())
			|| this->parser->getPeekCharacter() == '-') {
		error = NULL;
		operand = this->parser->readInt(flags->getMinOperand(),
				flags->getMaxOperand(), error);
		if (error != NULL) {
			delete flags;
			return NULL;
		}
		symbol = "";
	} else if (std::isalpha(this->parser->getPeekCharacter())) {
		operand = 0;
		error = NULL;
		symbol = this->parser->readSymbol(error);
		if (error != NULL) {
			delete flags;
			return NULL;
		}
	} else if (this->parser->getPeekCharacter() == '*') {
		operand = 0;
		symbol = "*";
	} else {
		std::string errMsg = "Invalid character '"
				+ std::to_string(this->parser->getPeekCharacter()) + "'!";
		error = new Error(this->parser->getLocation(), errMsg);
	}
	// check for indexed addressing (only if simple)
	error = NULL;
	bool tes = this->parser->skipIfIndexed(error);
	if (error != NULL) {
		delete flags;
		return NULL;
	}
	if (tes)
		flags->setIndexed();
	return new InstructionFormat3Extended(location, label, mnemonic, flags,
			operand, symbol);
}

Expression *OperandParser::parseExpression(Error *error) {
	error = NULL;
	Expression *expr = parser->getExpressionParser().parseExpression(error);
	if (error != NULL)
		return NULL;
	if (expr == NULL) {
		error = new Error(parser->getLocation(),
				"Expression expected '"
						+ std::to_string(parser->getPeekCharacter()) + "'!");
		return NULL;
	}
	return expr;
}

Command *OperandParser::parseDe(Location *location, std::string label,
		Mnemonic *mnemonic, Error *error) {
	error = NULL;
	Expression *expression = this->parseExpression(error);
	switch (mnemonic->getOpCode()) {
	case Opcode::START:
		return new START(location, label, mnemonic, expression);
	case Opcode::END:
		return new END(location, label, mnemonic, expression);
	}
	return NULL;
}

Command *OperandParser::parseSe(Location *location, std::string label,
		Mnemonic *mnemonic, Error *error) {
	return new RES(location, label, mnemonic);
}

Command *OperandParser::parseSd(Location *location, std::string label,
		Mnemonic *mnemonic, Error *error) {
	error = NULL;
	Data *data = this->parseData(mnemonic->getOpCode(), false, error);
	if (error != NULL)
		return NULL;
	return new StorageData(location, label, mnemonic, data, false);
}

Command *OperandParser::parseSd_(Location *location, std::string label,
		Mnemonic *mnemonic, Error *error) {
	error = NULL;
	Data *data = this->parseData(mnemonic->getOpCode(), true, error);
	if (error != NULL)
		return NULL;
	return new StorageData(location, label, mnemonic, data, false);
}

Command *OperandParser::parse(Location *location, std::string label,
		Mnemonic *mnemonic, Error *error) {
	error = NULL;
	switch (mnemonic->getType()) {
	case 0:
		return this->parseF3(location, label, mnemonic, error);
	case 1:
		return this->parseF3Extended(location, label, mnemonic, error);
	case 2:
		return this->parseDe(location, label, mnemonic, error);
	case 3:
		return this->parseSe(location, label, mnemonic, error);
	case 4:
		return this->parseSd(location, label, mnemonic, error);
	case 5:
		return this->parseSd_(location, label, mnemonic, error);
	}
	return NULL;
}
