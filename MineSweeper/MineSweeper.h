#pragma once
#include <vector>
#include "Tile.h"

class MineSweeper {
public:
	// Specifies if game is run in console or in window
	enum gameType { CONSOLE, WINDOW };

	// Construct a new default Mine Sweeper object
	MineSweeper();

	// Construct a new parameterized Mine Sweeper object
	MineSweeper(unsigned int boardWidth, unsigned int boardHeight, unsigned int bombsCount);

	// Destroy the Mine Sweeper object
	~MineSweeper();

	// Starts the chosen game type
	void start(gameType);

private:
	// Starts Console mode
	void startConsoleGame();

	// Starts Window mode
	void startWindowGame();

	// Initializes mBoard
	void initBoard();

	// Get the value of the specified board tile
	Tile getBoardTile(unsigned int row, unsigned int col);
	Tile getBoardTile(int index);

	// Set the value of the specified board tile
	void setBoardTileValue(unsigned int row, unsigned int col, int value);

	// Helper function showing values stored in mBoard
	void showBoardValues();

	// Starts all of the filling functions 
	void fillBoard();

	// Fills the board randomly with bombs represented as "-1"
	void fillBoardWithBombs();

	// Fills the board with values representing number of bombs nearby
	void fillBoardWithNumbers();

	// Checks if specified tile exists
	bool doesTileExist(int tileIndex);

	// Checks if the tile with next index is on another row
	bool isNextTileOnAnotherRow(int tileIndex);
	
	// Checks if the tile with previous index is on another row
	bool isPreviousTileOnAnotherRow(int tileIndex);

	// Checks if tile is valid, runs other validation methods
	bool isTileValid(int tileIndex);

	// Increments the tile values near the bomb
	void increaseTileValuesNearBomb(int bombIndex);

	// Board dimensions and bomb count on the board
	unsigned int mWidth, mHeight, mBombsCount;

	// Board represented as std::vector to allow use of "std::sample"
	std::vector<Tile> mBoard;

	// Vector representing the bomb indexes in the mBoard
	std::vector<int> mBombsIndexList;

	// Board width * board height
	int mBoardSize;
};
