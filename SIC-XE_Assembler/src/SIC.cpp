/*
 * SIC.cpp
 *
 *  Created on: 6 May 2017
 *      Author: heshamelsawaf
 */

#include "SIC.h"

SIC::SIC() {
	// TODO Auto-generated constructor stub

}

SIC::~SIC() {
	// TODO Auto-generated destructor stub
}

bool SIC::isDisp(int val) {
	return SIC::MIN_SICADDR <= val && val <= SIC::MAX_SICADDR;
}
