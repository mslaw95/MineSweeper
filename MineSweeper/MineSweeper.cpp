#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include "MineSweeper.h"

MineSweeper::MineSweeper() : mWidth(3), mHeight(3), mBombsCount(3) {
	mBoardSize = mWidth*mHeight;
}

MineSweeper::MineSweeper(unsigned int boardWidth, unsigned int boardHeight, 
	unsigned int bombsCount) : mWidth(boardWidth), mHeight(boardHeight), 
	mBombsCount(bombsCount) { 
	mBoardSize = mWidth*mHeight;
}

MineSweeper::~MineSweeper() { }

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
	fillBoard();
	showBoardValues();
	// FillBoardWithNumbers
	// HideBoardValues
	// RefreshBoard
	// IsBomb
	// GameLoop
	// Some algorithm to uncover all zeros at once
}

int MineSweeper::getBoardTileValue(unsigned int row, unsigned int col) {
	return mBoard[row + col*mWidth];
}

void MineSweeper::setBoardTileValue(unsigned int row, unsigned int col, int value) {
	mBoard[row + col*mWidth] = value;
}

void MineSweeper::showBoardValues() {
	for (int i = 1; i <= mBoardSize; ++i) {
		std::cout << mBoard[i - 1] << " ";
		if (!(i % mWidth)) std::cout << "\n";
	}
}

void MineSweeper::fillBoard() {
	fillBoardWithZeros();
	fillBoardWithBombs();
	fillBoardWithNumbers();
}

void MineSweeper::fillBoardWithZeros() {
	for (int i = 0; i < mBoardSize; ++i) {
		mBoard.push_back(0);
	}
}

void MineSweeper::fillBoardWithBombs() {
	std::vector<int> tilesIndexList(mBoardSize);
	std::vector<int> bombsIndexList;
	std::iota (std::begin(tilesIndexList), std::end(tilesIndexList), 0);

	std::sample(tilesIndexList.begin(), tilesIndexList.end(),
		std::back_inserter(bombsIndexList),
		mBombsCount,
		std::mt19937{std::random_device{}()}
	);

	for(auto index : bombsIndexList) {
		mBoard[index] = -1;
	}
}

void MineSweeper::fillBoardWithNumbers() {} // TODO next

void MineSweeper::startWindowGame() {} // TODO in vast future
