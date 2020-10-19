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
	// HideBoardValues
	// RefreshBoard
	// IsBomb
	// GameLoop
	// Some algorithm to uncover all zeros at once
}

int MineSweeper::getBoardTileValue(unsigned int row, unsigned int col) {
	return mBoard[col + row*mWidth];
}

void MineSweeper::setBoardTileValue(unsigned int row, unsigned int col, int value) {
	mBoard[col + row*mWidth] = value;
}

void MineSweeper::showBoardValues() {
	for (int i = 1; i <= mBoardSize; ++i) {
		std::cout << mBoard[i - 1] << " ";
		if (!(i % mWidth)) std::cout << "\n";
	}
}

bool MineSweeper::isBomb(unsigned int row, unsigned int col) {
	if (getBoardTileValue(row, col) == -1) {
		return true;
	}

	return false;
}

bool MineSweeper::isBomb(int index) {
	if (mBoard[index] == -1) {
		return true;
	}

	return false;
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
	std::iota (std::begin(tilesIndexList), std::end(tilesIndexList), 0);

	std::sample(tilesIndexList.begin(), tilesIndexList.end(),
		std::back_inserter(mBombsIndexList),
		mBombsCount,
		std::mt19937{std::random_device{}()}
	);

	for(auto index : mBombsIndexList) {
		mBoard[index] = -1;
	}
}

void MineSweeper::fillBoardWithNumbers() {
	for (auto index : mBombsIndexList) {
		increaseTileValuesNearBomb(index);
	}
}

bool MineSweeper::doesTileExist(int tileIndex) {
	if(tileIndex < 0 || tileIndex > mBoardSize) {
		return false;
	}

	return true;
}

bool MineSweeper::isNextTileOnAnotherRow(int tileIndex) {
	return !((tileIndex + 1) % mWidth) ? true : false;
}

bool MineSweeper::isPreviousTileOnAnotherRow(int tileIndex) {
	return !(tileIndex % mWidth) ? true : false;
}

bool MineSweeper::isTileValid(int tileIndex) {
	if (!doesTileExist(tileIndex)) return false;
	if (!isBomb(tileIndex)) return false;

	return true;
}

void MineSweeper::increaseTileValuesNearBomb(int bombIndex) {
if (!isNextTileOnAnotherRow(bombIndex)) {
	if (doesTileExist(bombIndex + 1) && !isBomb(bombIndex + 1)) 
		++mBoard[bombIndex + 1];
	if (doesTileExist(bombIndex + 1 - mWidth) && !isBomb(bombIndex + 1 - mWidth)) 
		++mBoard[bombIndex + 1 - mWidth];
	if (doesTileExist(bombIndex + 1 + mWidth) && !isBomb(bombIndex + 1 + mWidth)) 
		++mBoard[bombIndex + 1 + mWidth];
}
if (!isPreviousTileOnAnotherRow(bombIndex)) {
	if (doesTileExist(bombIndex - 1) && !isBomb(bombIndex - 1)) 
		++mBoard[bombIndex - 1];
	if (doesTileExist(bombIndex - 1 - mWidth) && !isBomb(bombIndex - 1 - mWidth)) 
		++mBoard[bombIndex - 1 - mWidth];
	if (doesTileExist(bombIndex - 1 + mWidth) && !isBomb(bombIndex - 1 + mWidth)) 
		++mBoard[bombIndex - 1 + mWidth];
}

if (doesTileExist(bombIndex - mWidth) && !isBomb(bombIndex - mWidth)) 
	++mBoard[bombIndex - mWidth];
if (doesTileExist(bombIndex + mWidth) && !isBomb(bombIndex + mWidth)) 
	++mBoard[bombIndex + mWidth];
}

void MineSweeper::startWindowGame() {} // TODO in vast future
