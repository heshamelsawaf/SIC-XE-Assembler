/*
 * Conversion.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_CONVERSION_H_
#define SRC_CONVERSION_H_

#include <string>
#include <vector>

class Conversion {
public:
	Conversion();
	virtual ~Conversion();
	static std::string bytesToHex(const std::vector<unsigned char>& data);
	static std::string bytesToHex(const std::vector<unsigned char>& data,
			int pos, int len);
	static std::string bytesToHexNice(std::vector<unsigned char>& data,
			int lim);
	static std::vector<unsigned char> hexToBytes(std::string str);
	static std::vector<unsigned char> hexToBytes(std::string str, int multiple);
	static std::string addressToHex(int address);
};

#endif /* SRC_CONVERSION_H_ */
