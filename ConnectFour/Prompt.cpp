#include "Prompt.h"
#include <iostream>

using namespace std;

void Prompt::welcome() {
	cout << "==== Connect Four ==============\n\n";
	cout << "Welcome to Connect Four!\n\n";
}

string Prompt::askName1() {
	string name;
	cout << "Player 1 tag: ";
	cin >> name;
	return name;
}

string Prompt::askName2() {
	string name;
	cout << "Player 2 tag: ";
	cin >> name;
	return name;
}

int Prompt::askRows() {
	int row;
	cout << "\nEnter board size between 4x4 & 10x10.\n\n";
	cout << "< Rows >\n";
	row = inputVal(4, 10);
	
	return row;
}

int Prompt::askCols() {
	int col;

	cout << "< Cols >\n";
	col = inputVal(4, 10);
	
	return col;
}

int Prompt::gameMode() {
	int input;

	cout << "Select a mode\n\n";
	cout << "0 - Quit\n"
		<< "1 - vs. Player\n"
		<< "2 - vs. CPU\n";
	input = inputVal(0, 2);

	return input;
}

int Prompt::askCoord(int colMax) {
	int y;
	cout << "Enter a column <=" << colMax << ":\n";
	y = inputVal(0, colMax);

	return y;
}

int Prompt::inputVal(int min, int max) {
	int input;
	bool invalid;
	do {
		cout << "Input: ";
		cin >> input;
		if (input < min || input > max) {
			cout << "Invalid input. Please try again.\n\n";
			invalid = true;
		}
		else
			invalid = false;
	} while (invalid);

	return input;
}