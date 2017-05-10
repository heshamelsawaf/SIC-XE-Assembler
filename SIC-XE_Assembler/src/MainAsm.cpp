/*
 * MainAsm.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include "MainAsm.h"
#include "Util.h"
#include "Logger.h"
#include "asm/Assembler.h"
#include <iostream>

MainAsm::MainAsm() {
	// TODO Auto-generated constructor stub

}

MainAsm::~MainAsm() {
	// TODO Auto-generated destructor stub
}

void MainAsm::handleArguments(const std::vector<std::string>* args) {
	std::string file = (*args)[args->size() - 1];
	std::string fileName = Util::getFileName(&file);
	this->buffer = Util::readFile(&file);
	this->listingFile.open(fileName + ".lst");
	if (this->listingFile.fail())
		Logger::err("Error creating listing file!");
	this->mapFile.open(fileName + ".map");
	if (this->mapFile.fail())
		Logger::err("Error creating map file!");
	this->objectFile.open(fileName + ".obj");
	if (this->objectFile.fail())
		Logger::err("Error creating object file!");
}

void MainAsm::handleSource() {
	Assembler assembler;
	ErrorController *errorCatcher = assembler.getErrorController();
	Prog *program = assembler.assemble(this->buffer);
	if (errorCatcher->count() > 0) {
		//new WriteErrors(program, errorCatcher).visitCommands();
		errorCatcher->print();
		return;
	}
	//
	assembler.generateListing(*program, listingFile);
	assembler.generateLog(*program, mapFile);
	assembler.generateObj(*program, objectFile, false);
}
