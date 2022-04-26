#pragma once
#ifndef PROMPT_H
#define PROMPT_H

#include <iostream>

using namespace std;

class Prompt {
public:
	void welcome();
	int askRows();
	int askCols();
	string askName1();
	string askName2();
	int gameMode();

	int askCoord(int colMax);
	int inputVal(int, int);
};

#endif // !PROMPT_H
