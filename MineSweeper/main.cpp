#include "MineSweeper.h"

int main() {
	unsigned int boardWidth = 5, boardHeight = 5, bombsCount = 10;
	MineSweeper game1;
	MineSweeper game2(boardWidth, boardHeight, bombsCount);

	game1.start(MineSweeper::CONSOLE);

	return 0;
}
