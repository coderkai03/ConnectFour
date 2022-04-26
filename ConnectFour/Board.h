#pragma once
#ifndef BOARD_H
#define BOARD_H

class Board {
private:
	char** board;
	int rows, cols;

	//StarSearch funcs
	bool vertSearch(int, int, int, int, char);
	bool horizSearch(int, int, int, int, char);
	bool URDiagSearch(int, int, int, int, char);
	bool DRDiagSearch(int, int, int, int, char);
public:
	Board(int, int);

	//getters
	int getRow() const { return rows; }
	int getCol() const { return cols; }
	char getCoord(int r, int c) const {return board[r][c];}

	//setters
	void setCoord(int, int, char);

	//misc
	int findXCoord(int);
	bool StarSearch(int, int, char, int, int, int, int);

	~Board();
	// * * * * * * * * * * 
	// * * * * * * X * * * 
	// * * * * * X * * * * 
	// * * * X X * * * * * 
	// * * * X * * * * * * 
	// * * * * * * * * * * 
	// * * * * * * * * * * 
	// * * * * * * * * * * 
	// * * * * * * * * * * 
	// * * * * * * * * * * 
};

#endif