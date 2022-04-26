#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int row, int col) {
	this->rows = row;
	this->cols = col;

	//create board
	board = new char* [rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new char[cols];
	}

	//fill board with *
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = '*';
		}
	}
}

Board::~Board() {
	for (int i = 0; i < rows; i++) { //delete every col array
		delete board[i];
	}

	delete[] board; //delete 1d array
}

void Board::setCoord(int x, int y, char c) {
	board[x][y] = c;
}

int Board::findXCoord(int y) {
	for (int i = rows - 1; i >= 0; i--)
		if (board[i][y] == '*') //if there is a space in that column
			return i;

	//there is no space in the column
	return -1;
}

bool Board::StarSearch(int x, int y, char token, int minRow, int maxRow, int minCol, int maxCol) {
	/* StarSearch: algo that finds a four-in-a-row (FiaR)
	 * 
	 * parameters:
	 * - coords: x, y
	 * - char to search for: token
	 * - search bounds: minRow, maxRow, minCol, maxCol
	 * 
	 * logic:
	 * - search the surrounding coords of one coord for FiaR (within search bounds)
	 * - search pattern occurs in star-shaped pattern; vertical, horiz, 2 diag axes
	 * - find 4 continuous coords in any one axis
	 * - searches are linear
	 * - restart linear search at each discontinuous coord
	 * 
	 * NOTES: 
	 * - axis searches do not occur if range is not >=4 length
	 * - returns true immediately if an axis search is successful
	 */

	const int MIN_LENGTH = 4;
	bool goodXRange = maxRow - minRow + 1 >= MIN_LENGTH;
	bool goodYRange = maxCol - minCol + 1 >= MIN_LENGTH;

	//search vertical range
	if (goodXRange) {
		if (vertSearch(minRow, maxRow, x, y, token))
			return true;
	}

	//search horizontal range
	if (goodYRange) {
		if (horizSearch(minCol, maxCol, x, y, token))
			return true;
	}

		/* Diag searches */

	if (goodXRange && goodYRange) {
		
			/* Up-right diag search */

		int leftRange, rightRange;
		bool goodURDiag, goodDRDiag;

		//find the shorter left range.
		if (maxRow - x < y - minCol) { //minrow is shorter. use minrow as reference
			leftRange = maxRow - x;
		}
		else { //mincol is shorter (or = minrow). use mincol as reference
			leftRange = y - minCol;
		}
		//find the shorter max range
		if (x - minRow < maxCol - y) { //minrow is shorter. use minrow as reference
			rightRange = x - minRow;
		}
		else { //maxCol is shorter (or = minrow). use mincol as reference
			rightRange = maxCol - y;
		}

		if (rightRange + leftRange + 1 >= MIN_LENGTH) {
			if (URDiagSearch(leftRange, rightRange, x, y, token))
				return true;
		}
		
			/* Down-right diag search */

		//find the shorter left range.
		if (x - minRow < y - minCol) { //minrow is shorter. use minrow as reference
			leftRange = x - minRow;
		}
		else { //mincol is shorter (or = minrow). use mincol as reference
			leftRange = y - minCol;
		}
		//find the shorter max range
		if (maxRow - x < maxCol - y) { //minrow is shorter. use minrow as reference
			rightRange = maxRow - x;
		}
		else { //maxCol is shorter (or = minrow). use mincol as reference
			rightRange = maxCol - y;
		}

		if (rightRange + leftRange + 1 >= MIN_LENGTH) {
			if (DRDiagSearch(leftRange, rightRange, x, y, token))
				return true;
		}
	}

	//by this point, no FiaRs exist
	return false;
}

bool Board::vertSearch(int minRow, int maxRow, int x, int y, char token) {
	int startRow, stopRow; //search bounds
	int total = 0; //count to FiaR

	//set row search range. should be 7 if min->max Row > 7
	if (maxRow - minRow + 1 < 7) { //min->max < 7 (implcitily >=4)
		stopRow = maxRow;
		startRow = minRow;
	}
	else { //min->max is >= 7, so let's keep it at 7
		if (x - minRow > 3) //upper range bigger than 3. keep at 3
			startRow = x - 3;
		else //upper range smaller than 3
			startRow = minRow;

		if (maxRow - x > 3) //lower range bigger than 3. keep at 3
			stopRow = x + 3;
		else //lower range smaller than 3
			stopRow = maxRow;
	}

	for (int i = startRow; i <= stopRow; i++) { //begin the search
		if (board[i][y] == token) {
			total++; //found continuity
		}
		else {
			total = 0; //lost continuity. restart count
		}

		if (total == 4) { //we found FiaR!!
			return true;
		}
	}

	return false; //no FiaR was found
}

bool Board::horizSearch(int minCol, int maxCol, int x, int y, char token) {
	int startCol, stopCol; //search bounds
	int total = 0; //count to FiaR

	//set row search range. should be 7 if min->max Row > 7
	if (maxCol - minCol + 1 < 7) { //min->max < 7 (implcitily >=4)
		stopCol = maxCol;
		startCol = minCol;
	}
	else { //min->max is >= 7, so let's keep it at 7
		if (y - minCol > 3) //upper range bigger than 3. keep at 3
			startCol = y - 3;
		else //upper range smaller than 3
			startCol = minCol;

		if (maxCol - y > 3) //lower range bigger than 3. keep at 3
			stopCol = y + 3;
		else //lower range smaller than 3
			stopCol = maxCol;
	}

	for (int i = startCol; i <= stopCol; i++) { //begin the search
		if (board[x][i] == token) {
			total++; //found continuity
		}
		else {
			total = 0; //lost continuity. restart count
		}

		if (total == 4) { //we found FiaR!!
			return true;
		}
	}

	return false; //no FiaR was found
}

bool Board::URDiagSearch(int leftRange, int rightRange, int x, int y, char token) {
	int startRow, stopRow, startCol, stopCol; //search bounds
	int total = 0; //count to FiaR

	for (int xCoord = x + leftRange, yCoord = y - leftRange; xCoord >= x - rightRange; xCoord--, yCoord++) {
		if (board[xCoord][yCoord] == token)
			total++; //found continuity
		else
			total = 0; //lost continuity. restart count
		
		if (total == 4) //we found FiaR
			return true;
	}

	return false; //no FiaR
}

bool Board::DRDiagSearch(int leftRange, int rightRange, int x, int y, char token) {
	int startRow, stopRow, startCol, stopCol; //search bounds
	int total = 0; //count to FiaR

	for (int xCoord = x - leftRange, yCoord = y - leftRange; xCoord <= x + rightRange; xCoord++, yCoord++) {
		if (board[xCoord][yCoord] == token)
			total++; //found continuity
		else
			total = 0; //lost continuity. restart count

		if (total == 4) //we found FiaR
			return true;
	}

	return false; //no FiaR
}