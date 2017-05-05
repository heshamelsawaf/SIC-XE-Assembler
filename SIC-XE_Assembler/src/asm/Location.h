/*
 * Location.h
 *
 *  Created on: 5 May 2017
 *      Author: heshamelsawaf
 */

#ifndef SRC_ASM_LOCATION_H_
#define SRC_ASM_LOCATION_H_

class Location {
public:
	Location(const int position, const int row, const int column);
	virtual ~Location();
	int getPositon() const;
	int getRow() const;
	int getColumn() const;
private:
	const int position;
	const int row;
	const int column;
};

#endif /* SRC_ASM_LOCATION_H_ */
