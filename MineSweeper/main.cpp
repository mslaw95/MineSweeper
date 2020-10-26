#include "MineSweeper.h"

int main() {
	unsigned int boardWidth = 5, boardHeight = 5, bombsCount = 10;
	MineSweeper mineSweeperDefault;
	MineSweeper mineSweeper(boardWidth, boardHeight, bombsCount);

	mineSweeperDefault.startGame();

	return 0;
}
