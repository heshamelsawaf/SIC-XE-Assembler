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
	Location(int position, int row, int column);
	virtual ~Location();
	int getPositon() const;
	int getRow() const;
	int getColumn() const;
	Location *clone() const;
private:
	int position;
	int row;
	int column;
};

#endif /* SRC_ASM_LOCATION_H_ */
