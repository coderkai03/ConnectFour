#pragma once
#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "Player.h"
#include "Board.h"

class ConnectFour {
private:
	Player* plyr1;
	Player* plyr2;
	Board* board;
	int plyrturn = 1;
	bool gameOver = false;
public:
	ConnectFour(int, int, Player*, Player*);

	//getters
	Player* getPlyr(int);
	int getPlyrTurn() { return plyrturn; }
	Board* getBoard() const { return board; }
	bool getGameOver() const { return gameOver; }

	//setters
	void setPlyrs(Player, Player);
	void setGameOver(bool status) { gameOver = status; }

	void takePlyrTurns(int, int); //switches between turns of the players
	void plyrDropChip(int, int, int);
	//void AIDropChip();
	int checkCoords(int);

	~ConnectFour();
};

#endif // !CONNECTFOUR_H
