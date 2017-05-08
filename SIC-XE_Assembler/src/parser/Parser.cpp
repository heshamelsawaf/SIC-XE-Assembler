/*
 * Parser.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Parser.h"
#include "../tree/Prog.h"
#include "../tree/Comment.h"

Parser::Parser(Mnemonics *mnemonics, ErrorController *errorController) {
	this->mnemonics = mnemonics;
	this->operandParser = new OperandParser(this);
	this->errorController = errorController;
	this->expressionParser = new ExpressionParser(this);
	this->program = NULL;
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

void Parser::checkWhitespace(std::string fmt, Error *error) {
	if (std::isspace(this->previousCharacter)) {
		error = new Error(this->getLocation(), fmt);
		return;
	}
}

OperandParser &Parser::getOperandParser() const {
	return *(this->operandParser);
}

Mnemonics &Parser::getMnemonics() const {
	return *(this->mnemonics);
}

Prog &Parser::getProgram() const {
	return *(this->program);
}

ExpressionParser &Parser::getExpressionParser() const {
	return *(this->expressionParser);
}

Command *Parser::parseIfCommand(Error *error) {
	Location *loc = this->getLocation();
	std::string label = this->readIfLabel();
	this->skipWhitespace();
	if (label.compare("")) {
		error = NULL;
		this->checkWhitespace("Missing whitespace after label '" + label + "'!",
				error);
		if (error != NULL) {
			delete loc;
			return NULL;
		}
	} else {
		delete loc;
		loc = NULL;
		loc = this->getLocation();
	}
	std::string name = this->readIfMnemonic();
	if (!(name.compare(""))) {
		if (!(label.compare(""))) {
			delete loc;
			loc = NULL;
			return NULL; // no instruction present
		}
		error = new Error(loc, "Missing mnemonic");
		return NULL;
	}
	Mnemonic *mnemonic = this->mnemonics->get(name);
	if (mnemonic == NULL) {
		error = new Error(loc, "Invalid mnemonic '" + name + "'!");
		return NULL;
	}
	this->skipWhitespace();
	error = NULL;
	Command *ret = this->operandParser->parse(loc, label, mnemonic, error);
	if (error != NULL)
		return NULL;
	return ret;
}

Prog *Parser::parseProgram() {
	this->program = new Prog();
	// advance to the beginning of command
	while (this->isReady() && this->getColumn() > 1)
		this->advancePointerUntil('\n');
	// do the lines
	while (this->isReady()) { // column must be equal to 1;
		Location *lineLoc = this->getLocation();
		Command *command;
		std::string comment;
		Error *error = NULL;
		command = this->parseIfCommand(error);
		if (error != NULL) {
			this->errorController->add(error);
			this->advancePointerUntil('\n');
			continue;
		}
		this->skipWhitespace();
		comment = readIfComment(false, false);
		if (command == NULL && !(comment.compare(""))) {
			Error *error = NULL;
			this->advancePointer('\n', error);
			if (error != NULL) {
				this->errorController->add(error);
				this->advancePointerUntil('\n');
				continue;
			}
		} // advance over the empty line

		// check what we got
		if (command != NULL) {
			// command with possible comment
			command->setComment(comment);
			Error *error = NULL;
			command->append(*program, error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
		} else if (comment.compare("")) {
			// only comment
			command = new Comment(lineLoc, comment);
			Error *error = NULL;
			command->append(*program, error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
		} else {

			command = new Comment(lineLoc, "");
			Error *error = NULL;
			command->append(*program, error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
		}
	}
	program->flushAllLiterals();
	return program;
}

