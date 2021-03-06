#pragma once
#include <vector>
#include "Tile.h"

class MineSweeper {
public:
	// Construct a new default Mine Sweeper object
	MineSweeper();

	// Construct a new parameterized Mine Sweeper object
	MineSweeper(unsigned int boardWidth, unsigned int boardHeight, unsigned int bombsCount);

	// Destroy the Mine Sweeper object
	~MineSweeper();

	// Starts the chosen game type
	void startGame();

private:
	// Starts the game
	void start();

	// Pints menu for the game
	void printMenu();

	// Initializes mBoard
	void initBoard();

	// Game loop
	void gameLoop();

	// Get player input of chosen tile
	void getPlayerInput(int& row, int& col, char& flag);

	// Get player input for row, col and flag
	int getRowInput();
	int getColInput();
	char getFlagInput();

	// Get the value of the specified board tile
	Tile* getBoardTile(unsigned int row, unsigned int col);
	Tile* getBoardTile(int index);

	// Helper function showing values stored in mBoard
	void showBoard();
	
	// Prints sign on the board depending on tile's properties
	void printSignForTile(Tile boardTile);

	// Generates new board 
	void generateBoard();

	// Returns the board to its initial state
	void cleanBoard();

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
	int mWidth, mHeight, mBombsCount;

	// Board represented as std::vector to allow use of "std::sample"
	std::vector<Tile> mBoard;

	// Vector representing the bomb indexes in the mBoard
	std::vector<int> mBombsIndexList;

	// Board width * board height
	int mBoardSize;
};
