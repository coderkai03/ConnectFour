#pragma once
#ifndef VIEW_H
#define VIEW_H

#include "Board.h"
#include <iostream>

using namespace std;

class View {
public:
	void displayBoard(Board *gameBoard);
	void displayTurn(string, Board*);
	void congrats(string);
};

#endif // !VIEW_H
