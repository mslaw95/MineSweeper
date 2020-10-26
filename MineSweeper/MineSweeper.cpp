#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <stdlib.h>
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

void MineSweeper::startGame() {
	printMenu();
	int playersChoice;
	std::cin >> playersChoice;
	system("CLS");
	switch (playersChoice) {
		case 1:
			generateBoard();
			gameLoop();
			startGame();
			break;
		case 2:
			std::cout << "ASD\n\n";
			system("PAUSE");
			startGame();
			break;
		case 3:
			std::cout << "Legend:\n# - Hidden tile\n@ - Flagged tile\nX - Bomb\n\n";
			system("PAUSE");
			startGame();
			break;
		case 4:
			return;
	}
}

void MineSweeper::printMenu() {
	system("CLS");
	std::cout << "Menu\n";
	std::cout << "1. New game\n";
	std::cout << "2. Instructions\n";
	std::cout << "3. Legend\n";
	std::cout << "4. Exit\n";
}

// TODO - write into smaller functions
// TODO - Some algorithm to uncover all zeros at once
void MineSweeper::gameLoop() {
	bool gameEnded = false;
	int row, col;
	char flag;

	while(!gameEnded) {
		// Refresh the board after every move
		showBoard();

		// TODO - Protect from entering wrong type e.g. letter 
		// TODO - Protect from entering non existing row/column
		// Enter row, col and flag
		std::cout << "Enter row number (starts from 1): ";
		std::cin >> row;
		std::cout << "Enter column number (starts from 1): ";
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
					system("PAUSE");
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

Tile* MineSweeper::getBoardTile(unsigned int row, unsigned int col) {
	return &mBoard[col + row*mWidth];
}

Tile* MineSweeper::getBoardTile(int index) {
	return &mBoard[index];
}

void MineSweeper::showBoard() {
	// Print board
	system("CLS");
	for (int i = 1; i <= mBoardSize; ++i) {
		Tile boardTile = mBoard[i - 1];

		// Choose proper sign for the tile
		printSignForTile (boardTile);

		// Newline when row ends
		if (!(i % mWidth)) {
			std::cout << "\n";
		}
	}
	std::cout << "\n";
}

void MineSweeper::printSignForTile(Tile boardTile) {
	if (boardTile.isHidden() && boardTile.isFlagged()) {
		std::cout << " @ ";
	} else if (boardTile.isHidden() && !boardTile.isFlagged()) {
		std::cout << " # ";
	} else if (!boardTile.isHidden() && !boardTile.isFlagged() && boardTile.isBomb()) {
		std::cout << " X ";
	} else {
		std::cout << " " << boardTile.getValue() << " ";
	}
}

void MineSweeper::generateBoard() {
	cleanBoard();
	initBoard();
	fillBoardWithBombs();
	fillBoardWithNumbers();
}

void MineSweeper::cleanBoard() {
	mBombsIndexList.clear();
	mBoard.clear();
}

void MineSweeper::initBoard() {
	for (int i = 0; i < mBoardSize; ++i) {
		Tile tile;
		mBoard.push_back(tile);
	}
}

void MineSweeper::fillBoardWithBombs() {
	std::vector<int> tilesIndexList(mBoardSize);
	std::iota (std::begin(tilesIndexList), std::end(tilesIndexList), 0);

	// Random bomb generation
	std::sample (tilesIndexList.begin(), tilesIndexList.end(),
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
