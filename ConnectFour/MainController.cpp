#include <cstdlib>
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Prompt.h"
#include "View.h"
#include "ConnectFour.h"
#include <ctime>

using namespace std;

void randYCoord(int&, int);

void PvAIMoves(ConnectFour*, Prompt, bool&);

void PvPMoves(ConnectFour*, Prompt, bool&);

void showTurn(ConnectFour*, View, bool);

void clearScreen() {
	cout << "================================\n\n";
}

int main() {
	//srand time
	srand(time(0));

	//Vars
	Prompt prompt;
	ConnectFour* game = nullptr;
	Player* p1 = nullptr;
	Player* p2 = nullptr;
	View display;

	int input;
	bool PvAI;
	bool PvP;

	/* Welcome */
	prompt.welcome();
	input = prompt.gameMode();
	clearScreen();

	/* Set up */
	if (input == 1) { //PvP game
		PvP = true;
		PvAI = false;
		p1 = new Player(prompt.askName1());
		p2 = new Player(prompt.askName2());
	}
	else if (input == 2) { //PvAI game
		PvAI = true;
		PvP = false;
		p1 = new Player(prompt.askName1());
		p2 = new Player("AI");
	}
	else
		exit(0);

	//Create game/assign players to game
	game = new ConnectFour(prompt.askCols(), prompt.askRows(), p1, p2);

	clearScreen();

	/* Gameplay */

	//Player vs. Player
	if (PvP)
		do {
			showTurn(game, display, PvP); //Show PvP board

			PvPMoves(game, prompt, PvP); //Make PvP move

			clearScreen(); //clear screen
		} while (!game->getGameOver());

	//Player vs. AI
	if (PvAI)
		do {
			showTurn(game, display, PvAI); //Show PvAI board

			PvAIMoves(game, prompt, PvAI); //Make PvAI move

			clearScreen(); //clear screen
		} while (!game->getGameOver());
	
	//By now, there is a winner. congratulate.
	if (game->getPlyrTurn() != 1)
		display.congrats(game->getPlyr(1)->getName());
	else
		display.congrats(game->getPlyr(2)->getName());

	//display board
	display.displayBoard(game->getBoard());

	clearScreen();

	//del controller ptrs
	delete game;

	return 0;
}

void showTurn(ConnectFour* game, View view, bool turn) {
	//display the next turn
	//parameters:		 player name,				  board
	if (turn)
		view.displayTurn(game->getPlyr(1)->getName(), game->getBoard());
	else
		view.displayTurn(game->getPlyr(2)->getName(), game->getBoard());
}

void randYCoord(int& y, int col) { //generate rand AI y coord
	y = rand() % col;
}


void PvPMoves(ConnectFour* game, Prompt prompt, bool& turn) {
	int x, y;
	bool good = true;

	do {
		y = prompt.askCoord(game->getBoard()->getCol()) - 1;
		x = game->checkCoords(y);
		if (x == -1) {
			good = false;
			cout << "\nColumn is full! Try again.\n\n";
		}
		else
			good = true;

	} while (!good); //check if coord is avail

	//place token on the board and update token bounds
	if (turn) {
		turn = false;
	}
	else {
		turn = true;
	}

	game->getPlyr(game->getPlyrTurn())->updateBounds(x, y); //update player bounds
	game->takePlyrTurns(x, y); //plots the coord on the board
	if (!turn)
		game->setGameOver(game->getBoard()->StarSearch(x, y, 'X', game->getPlyr(1)->getMinRow(), game->getPlyr(1)->getMaxRow(), game->getPlyr(1)->getMinCol(), game->getPlyr(1)->getMaxCol()));
	else
		game->setGameOver(game->getBoard()->StarSearch(x, y, 'O', game->getPlyr(2)->getMinRow(), game->getPlyr(2)->getMaxRow(), game->getPlyr(2)->getMinCol(), game->getPlyr(2)->getMaxCol()));
}

void PvAIMoves(ConnectFour* game, Prompt prompt, bool& plyrMove) {
	int x, y;
	bool good = true;
	/* PvAI */
	if (plyrMove) { //player moves
		do {
			y = prompt.askCoord(game->getBoard()->getCol()) - 1;
			x = game->checkCoords(y);
			if (x == -1) {
				good = false;
				cout << "\nColumn is full! Try again.\n\n";
			}
			else
				good = true;
		} while (!good); //check if coord is avail

		plyrMove = false;
	}
	else { //AI moves
		do { //rand gen a Y coord, then find respective X coord. regen if X coord not found
			randYCoord(y, game->getBoard()->getCol());
			x = game->checkCoords(y);
			if (x == -1) {
				good = false;
			}
			else
				good = true;
		} while (!good);

		plyrMove = true;
	}

	game->getPlyr(game->getPlyrTurn())->updateBounds(x, y); //update player bounds
	game->takePlyrTurns(x, y); //plots the coord on the board
	if (!plyrMove) {
		game->setGameOver(game->getBoard()->StarSearch(x, y, 'X', game->getPlyr(1)->getMinRow(), game->getPlyr(1)->getMaxRow(), game->getPlyr(1)->getMinCol(), game->getPlyr(1)->getMaxCol()));
	}
	else {
		game->setGameOver(game->getBoard()->StarSearch(x, y, 'O', game->getPlyr(2)->getMinRow(), game->getPlyr(2)->getMaxRow(), game->getPlyr(2)->getMinCol(), game->getPlyr(2)->getMaxCol()));
	}
}