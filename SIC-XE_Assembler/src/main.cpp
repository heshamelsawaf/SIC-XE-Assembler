/*
 * main.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include <iostream>
#include <vector>

#include "MainAsm.h"

int main(int argc, const char* argv[]) {
	if (argc > 1) {
		MainAsm m;
		std::vector<std::string> args(argv + 1, argv + argc);
		m.handleArguments(&args);
	}
	return 0;
}

