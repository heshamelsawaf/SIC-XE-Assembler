/*
 * ErrorController.h
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_ASM_ERRORCONTROLLER_H_
#define SRC_ASM_ERRORCONTROLLER_H_

#include <vector>
#include "Error.h"

class ErrorController {
public:
	ErrorController();
	virtual ~ErrorController();
	void add(Error *error);
	void clear();
	int count() const;
	void print();
	void printByRow(int row) const;
private:
	std::vector<Error *> errors;
	int last;
	void destroyPointers();
};

#endif /* SRC_ASM_ERRORCONTROLLER_H_ */
