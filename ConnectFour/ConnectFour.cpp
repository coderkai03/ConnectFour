#include "ConnectFour.h"

ConnectFour::ConnectFour(int cols, int rows, Player *p1, Player *p2) {
	board = new Board(rows, cols);

	//assign players
	plyr1 = p1;
	plyr2 = p2;

	//assign chip types (X or O)
	plyr1->setChipType('X');
	plyr2->setChipType('O');

	plyrturn = 1;
}

Player* ConnectFour::getPlyr(int id) {
	if (id == 1)
		return plyr1;
	else
		return plyr2;
}

void ConnectFour::takePlyrTurns(int x, int y) {
	if (plyrturn == 1) {
		plyr1->updateChips(x, y);
		plyrDropChip(1, x, y);
	}
	else {
		plyr2->updateChips(x, y);
		plyrDropChip(2, x, y);
	}

	//switch turns
	if (plyrturn == 1)
		plyrturn = 2;
	else
		plyrturn = 1;
}

void ConnectFour::setPlyrs(Player p1, Player p2) {
	plyr1 = &p1;
	plyr2 = &p2;
}

ConnectFour::~ConnectFour() {
	//players
	delete plyr1;
	delete plyr2;
	delete board;
}

void ConnectFour::plyrDropChip(int turn, int x, int y) {
	if (turn == 1) {
		board->setCoord(x, y, 'X');
	}
	else {
		board->setCoord(x, y, 'O');
	}
}

int ConnectFour::checkCoords(int y) {
	return board->findXCoord(y);
}