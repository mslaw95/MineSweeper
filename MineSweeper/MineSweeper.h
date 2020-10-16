#pragma once
#include <vector>

class MineSweeper {
public:
	/**
	 * @brief Specifies if game is run in console or in window
	 */
	enum gameType { CONSOLE, WINDOW };

	/**
	 * @brief Construct a new default Mine Sweeper object
	 */
	MineSweeper();

	/**
	 * @brief Construct a new parameterized Mine Sweeper object
	 * 
	 * @param boardWidth width of a game board representing rows
	 * @param boardHeight height of a game board representing columns
	 * @param bombsCount how many bombs should be set on the board
	 */
	MineSweeper(unsigned int boardWidth, unsigned int boardHeight, unsigned int bombsCount);

	/**
	 * @brief Destroy the Mine Sweeper object
	 */
	~MineSweeper();

	/**
	 * @brief Starts the chosen game type
	 */
	void start(gameType);

private:
	void startConsoleGame();
	void startWindowGame();

	/**
	 * @brief Get the value of the specified board tile
	 * 
	 * @param row specifies the row of a chosen tile
	 * @param col specifies the column of a chosen tile
	 * @return int returns the value of specified tile
	 */
	int getBoardTileValue(unsigned int row, unsigned int col);

	/**
	 * @brief Set the value of the specified board tile
	 * 
	 * @param row specifies the row of a chosen tile
	 * @param col specifies the column of a chosen tile
	 * @param value specifies what value is to be inserted
	 */
	void setBoardTileValue(unsigned int row, unsigned int col, int value);

	/**
	 * @brief Helper function showing values stored in mBoard
	 */
	void showBoardValues();

	/**
	 * @brief Starts all of the filling functions 
	 */
	void fillBoard();

	/**
	 * @brief Fills the vector representing board with zeros
	 */
	void fillBoardWithZeros();

	/**
	 * @brief Fills the board randomly with bombs represented as "-1"
	 */
	void fillBoardWithBombs();

	/**
	 * @brief Fills the board with values representing number of bombs nearby
	 */
	void fillBoardWithNumbers();

	/**
	 * @brief Board dimensions and bomb count on the board
	 */
	unsigned int mWidth, mHeight, mBombsCount;

	/**
	 * @brief Board represented as std::vector to allow use of "std::sample"
	 */
	std::vector<int> mBoard;

	/**
	 * @brief Board width * board height
	 */
	int mBoardSize;
};

