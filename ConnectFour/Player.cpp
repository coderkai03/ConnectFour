#include "Player.h"

Player::Player(string name) {
	this->name = name;
}

void Player::updateChips(int x, int y) {
	usedChips++;
}

void Player::updateBounds(int currX, int currY) {
	/* REMINDERS:
	 * - ONLY ONE FiaR NEEDED; RETURN IF FiaR IS FOUND
	 * - ONLY SEARCH BETWEEN MIN ROW/COL AND MAX ROW/COL
	 */
	
	//Set max/min rows
	if (currX < minRow)
		minRow = currX;
	if (currX > maxRow)
		maxRow = currX;

	//Set max/min cols
	if (currY < minCol)
		minCol = currY;
	if (currY > maxCol)
		maxCol = currY;
}