/*
 * SIC.h
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_SIC_H_
#define SRC_SIC_H_

class SIC {
public:
	SIC();
	virtual ~SIC();
	static const int SIZE_SICMEM = 1 << 15;  // 32 kB
	static const int MASK_SICADDR = 0x7FFF;
	static const int MIN_SICADDR = 0;
	static const int MAX_SICADDR = SIZE_SICMEM - 1;
	static bool isDisp(int val);
};

#endif /* SRC_SIC_H_ */
