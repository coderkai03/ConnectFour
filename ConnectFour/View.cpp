#include "View.h"
#include <iostream>

using namespace std;

void View::displayBoard(Board *gameBoard) {
	//set rows, cols
	int row = gameBoard->getRow();
	int col = gameBoard->getCol();

	//print col header (1-10)
	cout << " ";
	for (int i = 1; i <= col; i++)
		cout << i << " ";
	cout << endl;

	//print char board
	for (int i = 0; i < row; i++) { //loop 1st D
		cout << " ";
		for (int j = 0; j < col; j++) { // loop 2nd D
			//call board func to retrieve coord
			cout << gameBoard->getCoord(i, j) << " ";
		}
		cout << endl;
	}
}

void View::displayTurn(string name, Board* board) {
	cout << name << "'s turn\n\n";
	displayBoard(board);
}

void View::congrats(string name) {
	cout << name << " wins! Four in a row!\n\n";
}