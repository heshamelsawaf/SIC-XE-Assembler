/*
 * ErrorController.cpp
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#include "ErrorController.h"
#include "../Logger.h"

ErrorController::ErrorController() {
	this->last = 0;
}

ErrorController::~ErrorController() {
}

void ErrorController::add(const Error *error) {
	errors.push_back(error);
}

void ErrorController::clear() {
	this->errors.clear();
	this->last = 0;
}
int ErrorController::count() const {
	return this->errors.size();
}
void ErrorController::print() {
	for (; last < this->count(); last++)
		Logger::err(errors[last]->getError());
}
void ErrorController::printByRow(const int row) const {
	for (int i = 0; i < this->count(); i++)
		if (errors[i]->getErrorLocation().getRow() == row)
			Logger::err(errors[i]->getError());
}
