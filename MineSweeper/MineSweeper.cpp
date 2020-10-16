#include <iostream>
#include "MineSweeper.h"

MineSweeper::MineSweeper() : mWidth(3), mHeight(3), mBombsCount(3) {
	mBoard = new int[mWidth*mHeight];
}
MineSweeper::MineSweeper(unsigned int boardWidth, unsigned int boardHeight, 
	unsigned int bombsCount) : mWidth(boardWidth), mHeight(boardHeight), 
	mBombsCount(bombsCount) { 
	mBoard = new int[mWidth*mHeight];
}

void MineSweeper::start(gameType type) {
	switch (type) {
	case CONSOLE:
		startConsoleGame();
		break;
	case WINDOW:
		startWindowGame();
		break;
	default:
		break;
	}
}

void MineSweeper::startConsoleGame() { 
	std::cout << "Hello!\n";
	// FillBoardWithBombsAndZeros
	// FillBoardWithNumbers
	// ShowBoard
	// HideBoard
	// RefreshBoard
	// IsBomb
	// GameLoop
	// Some algorithm to uncover all zeros at once
}

int MineSweeper::getBoardTile(unsigned int row, unsigned int col) {
	return mBoard[row + col * mWidth];
}

void MineSweeper::startWindowGame() { } // TODO in future
