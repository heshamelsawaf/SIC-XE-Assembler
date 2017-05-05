/*
 * Mnemonics.cpp
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#include "Mnemonics.h"
#include "Opcode.h"

Mnemonics::Mnemonics() :
		mnemonicsMap(this->initMnemonics()) {
	// TODO Auto-generated constructor stub

}

Mnemonics::~Mnemonics() {
	for (std::map<std::string, Mnemonic*>::const_iterator i =
			this->mnemonicsMap.begin(); i != this->mnemonicsMap.end(); i++)
		delete i->second;
}

std::map<std::string, Mnemonic*> Mnemonics::initMnemonics() {
	std::map<std::string, Mnemonic*> map;
	map["RESB"] = new Mnemonic("RESB", Opcode::RESB);
	map["RESW"] = new Mnemonic("RESW", Opcode::RESW);
	map["BYTE"] = new Mnemonic("BYTE", Opcode::BYTE);
	map["WORD"] = new Mnemonic("WORD", Opcode::WORD);
	map["START"] = new Mnemonic("START", Opcode::START);
	map["END"] = new Mnemonic("END", Opcode::END);
	map["RD"] = new Mnemonic("RD", Opcode::RD);
	map["WD"] = new Mnemonic("WD", Opcode::WD);
	map["TD"] = new Mnemonic("TD", Opcode::TD);
	map["LDCH"] = new Mnemonic("LDCH", Opcode::LDCH);
	map["STCH"] = new Mnemonic("STCH", Opcode::STCH);
	map["JSUB"] = new Mnemonic("JSUB", Opcode::JSUB);
	map["RSUB"] = new Mnemonic("RSUB", Opcode::RSUB);
	map["AND"] = new Mnemonic("AND", Opcode::AND);
	map["OR"] = new Mnemonic("OR", Opcode::OR);
	map["JEQ"] = new Mnemonic("JEQ", Opcode::JEQ);
	map["JGT"] = new Mnemonic("JGT", Opcode::JGT);
	map["JLT"] = new Mnemonic("JLT", Opcode::JLT);
	map["J"] = new Mnemonic("J", Opcode::J);
	map["ADD"] = new Mnemonic("ADD", Opcode::ADD);
	map["SUB"] = new Mnemonic("SUB", Opcode::SUB);
	map["MUL"] = new Mnemonic("MUL", Opcode::MUL);
	map["DIV"] = new Mnemonic("DIV", Opcode::DIV);
	map["COMP"] = new Mnemonic("COMP", Opcode::COMP);
	map["TIX"] = new Mnemonic("TIX", Opcode::TIX);
	map["LDA"] = new Mnemonic("LDA", Opcode::LDA);
	map["LDX"] = new Mnemonic("LDX", Opcode::LDX);
	map["LDL"] = new Mnemonic("LDL", Opcode::LDL);
	map["STA"] = new Mnemonic("STA", Opcode::STA);
	map["STX"] = new Mnemonic("STX", Opcode::STX);
	map["STL"] = new Mnemonic("STL", Opcode::STL);
	return map;
}

