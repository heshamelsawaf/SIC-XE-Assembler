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
#include <fstream>

class MainAsm {
public:
	MainAsm();
	virtual ~MainAsm();
	void handleArguments(const std::vector<std::string>* args);
	void handleSource(void);
private:
	std::string buffer;
	std::ofstream listingFile;
	std::ofstream mapFile;
	std::ofstream objectFile;
};

#endif /* MAINASM_H_ */
