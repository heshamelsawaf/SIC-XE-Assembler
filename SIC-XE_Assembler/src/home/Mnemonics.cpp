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

Mnemonic *Mnemonics::get(std::string name) {
	if (this->mnemonicsMap.find(name) != this->mnemonicsMap.end())
		return mnemonicsMap[name];
	return NULL;
}

std::map<std::string, Mnemonic*> Mnemonics::initMnemonics() {
	std::map<std::string, Mnemonic*> map;
	map["RESB"] = new Mnemonic("RESB", Opcode::RESB, 3);
	map["RESW"] = new Mnemonic("RESW", Opcode::RESW, 3);
	map["BYTE"] = new Mnemonic("BYTE", Opcode::BYTE, 4);
	map["WORD"] = new Mnemonic("WORD", Opcode::WORD, 4);
	map["START"] = new Mnemonic("START", Opcode::START, 2);
	map["END"] = new Mnemonic("END", Opcode::END, 2);
	map["RD"] = new Mnemonic("RD", Opcode::RD, 1);
	map["WD"] = new Mnemonic("WD", Opcode::WD, 1);
	map["TD"] = new Mnemonic("TD", Opcode::TD, 1);
	map["LDCH"] = new Mnemonic("LDCH", Opcode::LDCH, 1);
	map["STCH"] = new Mnemonic("STCH", Opcode::STCH, 1);
	map["JSUB"] = new Mnemonic("JSUB", Opcode::JSUB, 1);
	map["RSUB"] = new Mnemonic("RSUB", Opcode::RSUB, 0);
	map["AND"] = new Mnemonic("AND", Opcode::AND, 1);
	map["OR"] = new Mnemonic("OR", Opcode::OR, 1);
	map["JEQ"] = new Mnemonic("JEQ", Opcode::JEQ, 1);
	map["JGT"] = new Mnemonic("JGT", Opcode::JGT, 1);
	map["JLT"] = new Mnemonic("JLT", Opcode::JLT, 1);
	map["J"] = new Mnemonic("J", Opcode::J, 1);
	map["ADD"] = new Mnemonic("ADD", Opcode::ADD, 1);
	map["SUB"] = new Mnemonic("SUB", Opcode::SUB, 1);
	map["MUL"] = new Mnemonic("MUL", Opcode::MUL, 1);
	map["DIV"] = new Mnemonic("DIV", Opcode::DIV, 1);
	map["COMP"] = new Mnemonic("COMP", Opcode::COMP, 1);
	map["TIX"] = new Mnemonic("TIX", Opcode::TIX, 1);
	map["LDA"] = new Mnemonic("LDA", Opcode::LDA, 1);
	map["LDX"] = new Mnemonic("LDX", Opcode::LDX, 1);
	map["LDL"] = new Mnemonic("LDL", Opcode::LDL, 1);
	map["STA"] = new Mnemonic("STA", Opcode::STA, 1);
	map["STX"] = new Mnemonic("STX", Opcode::STX, 1);
	map["STL"] = new Mnemonic("STL", Opcode::STL, 1);
	return map;
}

