#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include "MineSweeper.h"

MineSweeper::MineSweeper() : mWidth(3), mHeight(3), mBombsCount(3) {
	mBoardSize = mWidth*mHeight;
	initBoard();
}

MineSweeper::MineSweeper(unsigned int boardWidth, unsigned int boardHeight, 
	unsigned int bombsCount) : mWidth(boardWidth), mHeight(boardHeight), 
	mBombsCount(bombsCount) { 
	mBoardSize = mWidth*mHeight;
	initBoard();
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
	// HideBoardValues
	// RefreshBoard
	// GameLoop
	// Some algorithm to uncover all zeros at once
}

void MineSweeper::initBoard() {
	for (int i = 0; i < mBoardSize; ++i) {
		Tile tile;
		mBoard.push_back(tile);
	}
}

Tile MineSweeper::getBoardTile(unsigned int row, unsigned int col) {
	return mBoard[col + row*mWidth];
}

Tile MineSweeper::getBoardTile(int index) {
	return mBoard[index];
}

void MineSweeper::setBoardTileValue(unsigned int row, unsigned int col, int value) {
	mBoard[col + row*mWidth].setValue(value);
}

void MineSweeper::showBoardValues() {
	for (int i = 1; i <= mBoardSize; ++i) {
		std::cout << mBoard[i - 1].getValue() << " ";
		if (!(i % mWidth)) std::cout << "\n";
	}
}

void MineSweeper::fillBoard() {
	fillBoardWithBombs();
	fillBoardWithNumbers();
}

void MineSweeper::fillBoardWithBombs() {
	std::vector<int> tilesIndexList(mBoardSize);
	std::iota (std::begin(tilesIndexList), std::end(tilesIndexList), 0);

	std::sample(tilesIndexList.begin(), tilesIndexList.end(),
		std::back_inserter(mBombsIndexList),
		mBombsCount,
		std::mt19937{std::random_device{}()}
	);

	for(auto index : mBombsIndexList) {
		mBoard[index].setBomb();
	}
}

void MineSweeper::fillBoardWithNumbers() {
	for (auto index : mBombsIndexList) {
		increaseTileValuesNearBomb(index);
	}
}

bool MineSweeper::doesTileExist(int tileIndex) {
	return (tileIndex < 0 || tileIndex > mBoardSize) ? false : true;
}

bool MineSweeper::isNextTileOnAnotherRow(int tileIndex) {
	return !((tileIndex + 1) % mWidth) ? true : false;
}

bool MineSweeper::isPreviousTileOnAnotherRow(int tileIndex) {
	return !(tileIndex % mWidth) ? true : false;
}

bool MineSweeper::isTileValid(int tileIndex) {
	if (!doesTileExist(tileIndex)) return false;
	if (!getBoardTile(tileIndex).isBomb()) return false;

	return true;
}

// TODO make this into smaller functions
void MineSweeper::increaseTileValuesNearBomb(int bombIndex) {
	// Right column near bomb
	if (!isNextTileOnAnotherRow(bombIndex)) {
		// Right
		if (doesTileExist(bombIndex + 1) && 
			!getBoardTile(bombIndex + 1).isBomb()) {
			++mBoard[bombIndex + 1];
		}
		// Right up
		if (doesTileExist(bombIndex + 1 - mWidth) && 
			!getBoardTile(bombIndex + 1 - mWidth).isBomb()) {
			++mBoard[bombIndex + 1 - mWidth];
		}
		// Right below
		if (doesTileExist(bombIndex + 1 + mWidth) && 
			!getBoardTile(bombIndex + 1 + mWidth).isBomb()) {
			++mBoard[bombIndex + 1 + mWidth];
		}
	}
	// Left column near bomb
	if (!isPreviousTileOnAnotherRow(bombIndex)) {
		// Left
		if (doesTileExist(bombIndex - 1) && 
			!getBoardTile(bombIndex - 1).isBomb()) {
			++mBoard[bombIndex - 1];
		}
		// Left up
		if (doesTileExist(bombIndex - 1 - mWidth) && 
			!getBoardTile(bombIndex - 1 - mWidth).isBomb()) {
			++mBoard[bombIndex - 1 - mWidth];
		}
		//Left below
		if (doesTileExist(bombIndex - 1 + mWidth) && 
			!getBoardTile(bombIndex - 1 + mWidth).isBomb()) {
			++mBoard[bombIndex - 1 + mWidth];
		}
	}

	// Up 
	if (doesTileExist(bombIndex - mWidth) && 
		!getBoardTile(bombIndex - mWidth).isBomb()) {
		++mBoard[bombIndex - mWidth];
	}

	// Below
	if (doesTileExist(bombIndex + mWidth) && 
		!getBoardTile(bombIndex + mWidth).isBomb()) {
		++mBoard[bombIndex + mWidth];
	}
}

void MineSweeper::startWindowGame() {} // TODO in vast future