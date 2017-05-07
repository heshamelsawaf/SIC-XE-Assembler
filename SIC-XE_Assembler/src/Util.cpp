/*
 * Util.cpp
 *
 *  Created on: 4 May 2017
 *      Author: heshamelsawaf
 */

#include "Util.h"
#include "Logger.h"

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

std::string Util::readFile(std::ifstream* file) {
	if (file->fail()) {
		Logger::err("Error reading file!");
		return NULL;
	}
	std::string toBeReturned = "", line;
	while (std::getline(*file, line)) {
		toBeReturned += line + "\n";
	}
	return toBeReturned;
}

std::string Util::readFile(const std::string* file) {
	std::ifstream infile(*file);
	return Util::readFile(&infile);
}

std::string Util::getFileName(const std::string* file) {
	return file->substr(0, file->find_last_of("."));
}

