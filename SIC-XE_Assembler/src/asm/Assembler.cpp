/*
 * Assembler.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include "Assembler.h"

Assembler::Assembler() {
	this->errorController = new ErrorController();
	this->mnemonics = new Mnemonics();
	this->parser = new Parser(this->mnemonics, this->errorController);

}

Assembler::~Assembler() {
	delete this->errorController;
	delete this->mnemonics;
	delete this->parser;
	this->errorController = NULL;
	this->mnemonics = NULL;
	this->parser = NULL;
}

ErrorController *Assembler::getErrorController() const {
	return this->errorController;
}

Prog *Assembler::assemble(std::string input) {
	this->errorController->clear();

	this->parser->init(input);
	Prog *program = this->parser->parseProgram();
	return program;
}
void Assembler::generateListing(Prog &program, std::ofstream oBuffer) {

}
void Assembler::generateLog(Prog &program, std::ofstream oBuffer) {

}
void Assembler::generateObj(Prog &program, std::ofstream oBuffer,
		bool addSpaceInObj) {

}
