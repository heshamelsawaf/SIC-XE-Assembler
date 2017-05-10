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

std::string Conversion::bytesToHex(const std::vector<unsigned char>& data) {
	return Conversion::bytesToHex(data, 0, data.size());
}

std::string Conversion::bytesToHex(const std::vector<unsigned char>& data,
		int pos, int len) {
	char buffer[len * 2];
	for (int i = pos; i < pos + len && i < data.size(); i++)
		std::sprintf(buffer + (i * 2), "%02X", data[i]);
	std::string res = buffer;
	return res;
}

std::vector<unsigned char> Conversion::hexToBytes(std::string str) {
	return Conversion::hexToBytes(str, 1);
}

std::vector<unsigned char> Conversion::hexToBytes(std::string str,
		int multiple) {
	int len = str.length() / 2;
	len = (len + multiple - 1) / multiple * multiple;  // round up
	std::vector<unsigned char> res(len);
	for (int i = 0, j = 0; i < len; i++, j += 2) {
		std::string te = str.substr(j, 2);
		char f = te[0], s = te[1];
		int v = (16
				* (std::isalpha(f) ?
						f - 'a' >= 0 ? (f - 'a') + 10 : (f - 'A') + 10:f - '0'))
				+ (std::isalpha(s) ?
						s - 'a' >= 0 ? (s - 'a') + 10 : (s - 'A') + 10:s - '0');

		res[i] = (unsigned char) (v);
	}
	return res;
}

std::string Conversion::addressToHex(int address) {
	char buffer[5];
	std::sprintf(buffer, "%05X", address & 0xFFFFF);
	std::string res = buffer;
	return res;
}

std::string Conversion::bytesToHexNice(std::vector<unsigned char>& data,
		int lim) {
	if (data.size() > lim) {
		char buffer[8];
		std::sprintf(buffer, "%02X....%02X", data[0], data[data.size() - 1]);
		std::string res = buffer;
		return res;
	} else {
		char buffer[8];
		std::string b = Conversion::bytesToHex(data, 0, data.size());
		std::sprintf(buffer, "%-8s", b.c_str());
		std::string res = buffer;
		return res;
	}
}
