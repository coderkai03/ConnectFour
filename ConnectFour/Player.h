#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player {
private:
	string name;

	int usedChips = 0;

	//token identifier
	char chipType;

	//constraints for chip search - calibrate to OutOfBounds values
	int minRow = 11, maxRow = -1,
		minCol = 11, maxCol = -1;
public:
	
	Player(string);

	//setters
	void setName(string name) { this->name = name; }
	void setChipType(char type) { chipType = type; }

	//getters
	string getName() const { return name; }
	int getMinRow() const { return minRow; }
	int getMaxRow() const { return maxRow; }
	int getMinCol() const { return minCol; }
	int getMaxCol() const { return maxCol; }
	char getChipType() const { return chipType; }

	void updateChips(int, int);
	void updateBounds(int, int);
};

#endif // !PLAYER_H
