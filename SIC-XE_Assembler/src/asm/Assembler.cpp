/*
 * Assembler.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include "Assembler.h"

#include "../Conversion.h"
#include "../tree/Block.h"
#include "../tree/Comment.h"
#include "../tree/directives/END.h"
#include "../tree/directives/START.h"
#include "../tree/expression/Expression.h"
#include "../tree/instructions/InstructionFormat3Extended.h"
#include "../tree/storage/RES.h"
#include "../tree/Section.h"
#include "../tree/Symbols.h"
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
	program->switchDefault();
	for (Section *section : program->getSections()) {
		section->reset();
		for (Block *block : section->getBlocks())
			block->reset();
	}
	this->resolveBlocks(*program);
	program->switchDefault();
	for (Section *section : program->getSections()) {
		section->reset();
		for (Block *block : section->getBlocks())
			block->reset();
	}
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
	*error = NULL;
	d.resolve(program, error);
	if (*error != NULL)
		return;
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
void Assembler::generateListing(Prog &program, std::ofstream& oBuffer) {
	program.switchDefault();
	for (Section *section : program.getSections()) {
		section->reset();
		for (Block *block : section->getBlocks())
			block->reset();
	}
	for (Command *command : program.getCommands()) {
		Error *error = NULL;
		command->enter(program, &error);
		if (error != NULL) {
			this->errorController->add(error);
			continue;
		}
		if (Comment *t = dynamic_cast<Comment*>(command))
			oBuffer << "                  " << t->getComment() << "\n";
		else if (Command *t = dynamic_cast<Command*>(command)) {
			int labelLength = program.getMaxLabelLength();
			int nameLength = 6;
			std::string n = t->printMnemonicName();
			if (n.length() > 0 && (n[0] == '=' || n[0] == '+'))
				labelLength--, nameLength++;
			// location address
			oBuffer << Conversion::addressToHex(program.getLocationCounter())
					<< "  ";
//			// raw code
			std::vector<unsigned char> vec = command->burnObjectCode();
			oBuffer << Conversion::bytesToHexNice(vec, 4);
//			// label
			char buffer[7 + labelLength];
			std::string k = "  %-" + std::to_string(labelLength) + "s  ";
			std::sprintf(buffer, k.c_str(), command->getLabel().c_str());
			oBuffer << buffer;
//			// instruction
			char buffer1[6 + nameLength];
			k = "%-" + std::to_string(nameLength) + "s  ";
			std::sprintf(buffer1, k.c_str(), n.c_str());
			oBuffer << buffer1;
//			// operand
			oBuffer << command->printOperand();
//			// comment
			oBuffer << "    " << command->getComment();
			oBuffer << "\n";
		}
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
void Assembler::generateLog(Prog &program, std::ofstream& oBuffer) {
	program.switchDefault();
	for (Section *section : program.getSections()) {
		section->reset();
		for (Block *block : section->getBlocks())
			block->reset();
	}
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
		oBuffer << "***** Section " << section->print() << " *****\n";
		char buffer[100];
		std::sprintf(buffer,
				"Status: size=%d  blocks=%d  symbols=%d  literals=%d\n",
				section->getSectionSize(),
				section->getCurrentBlock().getBlockSize(),
				section->getSymbols().sortedV().size(),
				(int) section->getLiterals().getStorageSize());
		oBuffer << buffer;
//		// blocks
		oBuffer << "Blocks\n";
		oBuffer << "    name        start   size  #ins #dir #sto\n";
		for (Block *block : section->getBlocks()) {
			Error *error = NULL;
			block->enter(program, &error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
			std::sprintf(buffer, "    %-10s  %05X  %05X  %4d %4d %4d\n",
					block->print().c_str(), block->getBlockStartAddress(),
					block->getBlockSize(), block->getInstructionCounter(),
					block->getDirectiveCounter(), block->getStorageCounter());
			oBuffer << buffer;
			block->leave(program, &error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
		}
//		// symbols
		oBuffer << "Symbols\n";
		std::string k = "    %-" + std::to_string(program.getMaxLabelLength())
				+ "s      hex       dec     kind      description\n";
		std::sprintf(buffer, k.c_str(), "name");
		oBuffer << buffer;
		for (Symbol& symbol : section->getSymbols().sortedV()) {
			Error *error = NULL;
			symbol.enter(program, &error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
			std::string k = "    %-"
					+ std::to_string(program.getMaxLabelLength())
					+ "s   %06X  %8d     %-8s  %s\n";
			std::sprintf(buffer, k.c_str(), symbol.getSymbolName().c_str(),
					symbol.getValue(), symbol.getValue(),
					symbol.printType().c_str(),
					symbol.printExpression().c_str());
			oBuffer << buffer;
			symbol.leave(program, &error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
		}
//		// literals
		oBuffer << "Literals\n";
		int l = section->getLiterals().getMaxLabelLength();
		k = "    %-" + std::to_string(l) + "s  definition\n";
		std::sprintf(buffer, k.c_str(), "label");
		oBuffer << buffer;
		for (StorageData& lit : section->getLiterals().getStorage()) {
			std::string k = "    %-" + std::to_string(l) + "s  %s\n";
			std::sprintf(buffer, k.c_str(), lit.getLabel().c_str(),
					lit.print().c_str());
			oBuffer << buffer;
		}
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
void Assembler::generateObj(Prog &program, std::ofstream& oBuffer,
		bool addSpaceInObj) {
	std::string space = addSpaceInObj ? " " : "";
	program.switchDefault();
	for (Section *section : program.getSections()) {
		section->reset();
		for (Block *block : section->getBlocks())
			block->reset();
	}
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
		// header record
		int start =
				!(section->getSectionName().compare("")) ?
						program.getStartAddress() : 0;
		std::string name =
				!(section->getSectionName().compare("")) ?
						program.getName() : section->getSectionName();
		char buffer[100];
		std::sprintf(buffer, "H%s%-6s%s%06X%s%06X\n", space.c_str(),
				name.c_str(), space.c_str(), start, space.c_str(),
				section->getSectionSize());
		oBuffer << buffer;
		// text records
		int textAddr = start;
		std::string buff = "";

		for (Block *block : section->getBlocks()) {
			Error *error = NULL;
			block->enter(program, &error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
			for (Command *command : block->getCommands()) {
				Error *error = NULL;
				command->enter(program, &error);
				if (error != NULL) {
					this->errorController->add(error);
					continue;
				}
				if (command->getCommandSize() > 0)
					buff += space;
				bool flush = command->burnText(buff);
				if (flush || buff.length() > 54) {
					if (buff.length()) {
						std::sprintf(buffer, "T%s%06X%s%02X", space.c_str(),
								textAddr, space.c_str(), buff.length() / 2);
						oBuffer << buffer << buff << "\n";
						buff = "";
					}
					textAddr = program.getLocationCounter()
							+ command->getCommandSize();
				}
				command->leave(program, &error);
				if (error != NULL) {
					this->errorController->add(error);
					continue;
				}
			}
			block->leave(program, &error);
			if (error != NULL) {
				this->errorController->add(error);
				continue;
			}
		}
		if (buff.length()) {
			std::sprintf(buffer, "T%s%06X%s%02X", space.c_str(), textAddr,
					space.c_str(), buff.length() / 2);
			oBuffer << buffer << buff << "\n";
			buff = "";
		}
		int first =
				!(section->getSectionName().compare("")) ?
						program.getAddressOfFirstInstruction() : start;
		std::sprintf(buffer, "E%s%06X\n", space.c_str(), first);
		oBuffer << buffer;
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
