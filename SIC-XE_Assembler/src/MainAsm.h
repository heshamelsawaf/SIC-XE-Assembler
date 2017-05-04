/*
 * MainAsm.h
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#ifndef MAINASM_H_
#define MAINASM_H_

#include <string>
#include <vector>

class MainAsm {
public:
	MainAsm();
	virtual ~MainAsm();
	void handleArguments(const std::vector<std::string>* args);
	void handleSource(void);
};

#endif /* MAINASM_H_ */
