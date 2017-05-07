/*
 * Conversion.cpp
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#include "Conversion.h"
#include <cstdio>

Conversion::Conversion() {
	// TODO Auto-generated constructor stub

}

Conversion::~Conversion() {
	// TODO Auto-generated destructor stub
}

std::string Conversion::bytesToHex(unsigned char *data, int length) {
	return Conversion::bytesToHex(data, 0, length, length);
}

std::string Conversion::bytesToHex(unsigned char *data, int pos, int len,
		int length) {
	char buffer[length];
	for (int i = pos; i < pos + len && i < length; i++)
		std::sprintf(buffer, "%02X", data[i]);
	std::string res = buffer;
	return res;
}

void Conversion::hexToBytes(std::string str, unsigned char *data) {
	Conversion::hexToBytes(str, data, 1);
}

void Conversion::hexToBytes(std::string str, unsigned char *data,
		int multiple) {
	int len = str.length() / 2;
	len = (len + multiple - 1) / multiple * multiple;  // round up
	unsigned char res[len];
	for (int i = 0, j = 0; i < len; i++, j += 2) {
		std::string te = str.substr(j, 2);
		char f = te[0], s = te[1];
		int v = (16
				* (std::isalpha(f) ? f - 'a' >= 0 ? f - 'a' : f - 'A':f - '0'))
				+ (std::isalpha(s) ? s - 'a' >= 0 ? s - 'a' : s - 'A':s - '0');

		res[i] = (unsigned char) (v);
	}
	data = res;
}
