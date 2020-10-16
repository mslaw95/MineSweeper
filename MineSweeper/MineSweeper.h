#pragma once

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
	 * @brief Starts the chosen game type
	 */
	void start(gameType);

private:
	void startConsoleGame();
	void startWindowGame();

	/**
	 * @brief Get the value under specified board tile
	 * 
	 * @param row specifies the row of a chosen tile
	 * @param col specifies the column of a chosen tile
	 * @return int returns the value of specified tile
	 */
	int getBoardTile(unsigned int row, unsigned int col);

	unsigned int mWidth, mHeight, mBombsCount;
	int *mBoard;
};

