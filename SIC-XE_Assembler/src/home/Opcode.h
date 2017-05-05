/*
 * Opcode.h
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_HOME_OPCODE_H_
#define SRC_HOME_OPCODE_H_

class Opcode {
public:
	Opcode();
	virtual ~Opcode();
	static const int LDA = 0x00;
	static const int LDX = 0x04;
	static const int LDL = 0x08;
	static const int STA = 0x0C;
	static const int STX = 0x10;
	static const int STL = 0x14;
	// fixed point arithmetic
	static const int ADD = 0x18;
	static const int SUB = 0x1C;
	static const int MUL = 0x20;
	static const int DIV = 0x24;
	static const int COMP = 0x28;
	static const int TIX = 0x2C;
	// jumps
	static const int JEQ = 0x30;
	static const int JGT = 0x34;
	static const int JLT = 0x38;
	static const int J = 0x3C;
	// bit manipulation
	static const int AND = 0x40;
	static const int OR = 0x44;
	// jump to subroutine
	static const int JSUB = 0x48;
	static const int RSUB = 0x4C;
	// load and store int
	static const int LDCH = 0x50;
	static const int STCH = 0x54;
	// devices
	static const int RD = 0xD8;
	static const int WD = 0xDC;
	static const int TD = 0xE0;

	// ************ Directives ******************

	static const int START = 0;
	static const int END = 1;

	// Storage directives

	static const int RESB = 0;
	static const int RESW = 1;
	static const int BYTE = 3;
	static const int WORD = 4;
};

#endif /* SRC_HOME_OPCODE_H_ */
