/*
 * Assembler.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include "Assembler.h"

#include "../tree/Block.h"
#include "../tree/directives/START.h"
#include "../tree/directives/END.h"
#include "../tree/instructions/InstructionFormat3Extended.h"
#include "../tree/storage/RES.h"
#include "../tree/Section.h"
#include "Error.h"
#include "Location.h"

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
	program->switchDefault();
	for (Section *section : program->getSections()) {
		section->reset();
		for (Block *block : section->getBlocks())
			block->reset();
	}
	this->resolveAbsolute(*program);
	this->resolveBlocks(*program);
	this->resolveSymbols(*program);
	return program;
}

void Assembler::resolveBlocks(Prog& program) {
	Error *error = NULL;
	program.enter(program, &error);
	if (error != NULL) {
		this->errorController->add(error);
		return;
	}
	for (Section *section : program.getSections()) {
		Error *error = NULL;
		section->enter(program, &error);
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
		int blockStart =
				program.getCurrentSection().isDefaultSection() ?
						program.getStartAddress() : 0;
		int size = 0;
		for (Block *block : section->getBlocks()) {
			Error *error = NULL;
			block->setBlockStartAddress(blockStart);
			block->enter(program, &error);
			if (error != NULL) {
				this->errorController->add(error);
				blockStart += block->getBlockSize();
				size += block->getBlockSize();
				continue;
			}
			for (Command *command : block->getCommands()) {
				Error *error = NULL;
				command->enter(program, &error);
				if (error != NULL) {
					this->errorController->add(error);
					continue;
				}
				program.getCurrentSection().getSymbols().defineLabel(
						command->getLabel(), command->getLocation(),
						program.getLocationCounter(), &error);
				if (error != NULL) {
					this->errorController->add(error);
					continue;
				}
				command->leave(program, &error);
				if (error != NULL) {
					this->errorController->add(error);
					continue;
				}
			}
			block->leave(program, &error);
			if (error != NULL)
				this->errorController->add(error);
			blockStart += block->getBlockSize();
			size += block->getBlockSize();
		}
		section->setSectionSize(size);
		section->leave(program, &error);
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
	}
	program.leave(program, &error);
	if (error != NULL) {
		this->errorController->add(error);
		return;
	}
}

void Assembler::resolveAbsolute(Prog& program) {
	for (Command *command : program.getCommands()) {
		Error *error = NULL;
		command->enter(program, &error);
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
		if (START *t = dynamic_cast<START*>(command))
			this->visitSTART(program, *t, &error);
		else if (RES *t = dynamic_cast<RES*>(command))
			t->resolve(program, &error);
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
		command->leave(program, &error);
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
	}
}

void Assembler::visitSTART(Prog &program, START &d, Error** error) {
	if (program.getName().compare("")) {
		*error = new Error(d.getLocation(), "Multiple STARTs are not allowed");
		return;
	}
	if (program.getStartAddress() != program.getLocationCounter()) {
		*error = new Error(d.getLocation(),
				"START must precede all instructions");
		return;
	}
	if (d.getLabel().length() > 6) {
		*error = new Error(d.getLocation(), "Program name too long");
		return;
	}
	d.resolve(program);
	program.setName(d.getLabel());
	program.setStartAddress(d.getValue());
}

void Assembler::resolveSymbols(Prog& program) {
	for (Command *command : program.getCommands()) {
		Error *error = NULL;
		command->enter(program, &error);
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
		if (InstructionFormat3Extended *t =
				dynamic_cast<InstructionFormat3Extended*>(command))
			t->resolve(program, &error);
		else if (END *t = dynamic_cast<END*>(command))
			program.setAddressOfFirstInstruction(
					t->getExpression().evaluate(program, &error));
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
		command->leave(program, &error);
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
	}
}
void Assembler::generateListing(Prog &program, std::ofstream oBuffer) {

}
void Assembler::generateLog(Prog &program, std::ofstream oBuffer) {

}
void Assembler::generateObj(Prog &program, std::ofstream oBuffer,
		bool addSpaceInObj) {

}
