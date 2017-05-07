/*
 * Conversion.h
 *
 *  Created on: 7 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_CONVERSION_H_
#define SRC_CONVERSION_H_

#include <string>

class Conversion {
public:
	Conversion();
	virtual ~Conversion();
	static std::string bytesToHex(unsigned char *data, int length);
	static std::string bytesToHex(unsigned char *data, int pos, int len,
			int length);
	static void hexToBytes(std::string str, unsigned char *data);
	static void hexToBytes(std::string str, unsigned char *data, int multiple);
};

#endif /* SRC_CONVERSION_H_ */
