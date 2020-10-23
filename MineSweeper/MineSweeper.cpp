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
	// TODO - start menu (switch) + game tooltip
	generateBoard();
	gameLoop();
	// TODO - Some algorithm to uncover all zeros at once
}

// TODO - write into smaller functions
void MineSweeper::gameLoop() {
	bool gameEnded = false;
	int row, col;
	char flag;

	while(!gameEnded) {
		// Refresh the board after every move
		showBoard();

		// Enter coords and flag
		std::cout << "Enter row: ";
		std::cin >> row;
		std::cout << "Enter column: ";
		std::cin >> col;
		std::cout << "Do you want to flag (y, n): ";
		std::cin >> flag;
		
		// Get pointer to the specified tile
		Tile* boardTile = getBoardTile(row - 1, col - 1);

		// Check if tile was flagged
		if (flag == 'y') {
			boardTile->setFlag();
		} else {
			// Check if tile isn't flagged already
			if (!boardTile->isFlagged()) {
				// Check if bomb was hit
				if (boardTile->isBomb()) {
					boardTile->reveal();
					showBoard();
					std::cout << "You Lost!\n";
					gameEnded = true;
				// Reveal tile if all checks passed
				} else {
					boardTile->reveal();
				}
			}
		}
		
		// Check if only bombs are left unrevealed
		for (int i = 0; i < mBoardSize; ++i) {
			boardTile = getBoardTile(i);
			if (!boardTile->isBomb() && boardTile->isHidden()) {
				break;
			} 
			
			if (i == mBoardSize - 1) {
				std::cout << "Gratulations, You Won!\n";
				gameEnded = true;
				break;
			}
		}
	}
}

void MineSweeper::initBoard() {
	for (int i = 0; i < mBoardSize; ++i) {
		Tile tile;
		mBoard.push_back(tile);
	}
}

Tile* MineSweeper::getBoardTile(unsigned int row, unsigned int col) {
	return &mBoard[col + row*mWidth];
}

Tile* MineSweeper::getBoardTile(int index) {
	return &mBoard[index];
}

void MineSweeper::setBoardTileValue(unsigned int row, unsigned int col, int value) {
	mBoard[col + row*mWidth].setValue(value);
}

void MineSweeper::showBoard() {
	// TODO - Legend at the top of the board
	std::cout << "\n";
	for (int i = 1; i <= mBoardSize; ++i) {
		Tile boardTile = mBoard[i - 1];
		if (boardTile.isHidden() && boardTile.isFlagged()) {
			std::cout << " @ ";
		} else if (boardTile.isHidden() && !boardTile.isFlagged()) {
			std::cout << " # ";
		} else if (!boardTile.isHidden() && !boardTile.isFlagged() && boardTile.isBomb()) {
			std::cout << " X ";
		} else {
			std::cout << " " << boardTile.getValue() << " ";
		}

		if (!(i % mWidth)) std::cout << "\n";
	}
}

void MineSweeper::generateBoard() {
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
	if (!getBoardTile(tileIndex)->isBomb()) return false;

	return true;
}

// TODO - write into smaller functions
void MineSweeper::increaseTileValuesNearBomb(int bombIndex) {
	// Right column near bomb
	if (!isNextTileOnAnotherRow(bombIndex)) {
		// Right
		if (doesTileExist(bombIndex + 1) && 
			!getBoardTile(bombIndex + 1)->isBomb()) {
			++mBoard[bombIndex + 1];
		}
		// Right up
		if (doesTileExist(bombIndex + 1 - mWidth) && 
			!getBoardTile(bombIndex + 1 - mWidth)->isBomb()) {
			++mBoard[bombIndex + 1 - mWidth];
		}
		// Right below
		if (doesTileExist(bombIndex + 1 + mWidth) && 
			!getBoardTile(bombIndex + 1 + mWidth)->isBomb()) {
			++mBoard[bombIndex + 1 + mWidth];
		}
	}
	// Left column near bomb
	if (!isPreviousTileOnAnotherRow(bombIndex)) {
		// Left
		if (doesTileExist(bombIndex - 1) && 
			!getBoardTile(bombIndex - 1)->isBomb()) {
			++mBoard[bombIndex - 1];
		}
		// Left up
		if (doesTileExist(bombIndex - 1 - mWidth) && 
			!getBoardTile(bombIndex - 1 - mWidth)->isBomb()) {
			++mBoard[bombIndex - 1 - mWidth];
		}
		//Left below
		if (doesTileExist(bombIndex - 1 + mWidth) && 
			!getBoardTile(bombIndex - 1 + mWidth)->isBomb()) {
			++mBoard[bombIndex - 1 + mWidth];
		}
	}

	// Up 
	if (doesTileExist(bombIndex - mWidth) && 
		!getBoardTile(bombIndex - mWidth)->isBomb()) {
		++mBoard[bombIndex - mWidth];
	}

	// Below
	if (doesTileExist(bombIndex + mWidth) && 
		!getBoardTile(bombIndex + mWidth)->isBomb()) {
		++mBoard[bombIndex + mWidth];
	}
}

void MineSweeper::startWindowGame() {} // TODO - in vast future (optional)