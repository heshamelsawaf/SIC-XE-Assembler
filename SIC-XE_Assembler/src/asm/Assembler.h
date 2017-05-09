/*
 * Assembler.h
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_ASM_ASSEMBLER_H_
#define SRC_ASM_ASSEMBLER_H_

#include "ErrorController.h"
#include "../home/Mnemonics.h"
#include "../parser/Parser.h"
#include "../tree/Prog.h"
#include <string>
#include <fstream>

class START;

class Assembler {
public:
	Assembler();
	virtual ~Assembler();
	Prog *assemble(std::string input);
	void generateListing(Prog &program, std::ofstream oBuffer);
	void generateLog(Prog &program, std::ofstream oBuffer);
	void generateObj(Prog &program, std::ofstream oBuffer, bool addSpaceInObj);
	ErrorController *getErrorController() const;

private:
	ErrorController *errorController;
	Mnemonics *mnemonics;
	Parser *parser;
	void visitSTART(Prog &program, START &d, Error** error);
	void resolveAbsolute(Prog& program);
	void resolveBlocks(Prog& program);
	void resolveSymbols(Prog& program);
};

#endif /* SRC_ASM_ASSEMBLER_H_ */
