#pragma once

class Tile {
public:
    // Checks if bomb is on the tile
    bool isBomb();
    
    // Checks if tile is hidden
    bool isHidden();
    
    // Checks if tile is flagged
    bool isFlagged();

    // Gets the value of the tile
	int getValue();

    // Sets the value of the tile
	void setValue(int value);

    // Sets the tile to be a bomb
    void setBomb();

    // Flags the tile
    void setFlag();

    // Reveals the tile
    void reveal();

    // Hides the tile
    void hide();

    // Allows incrementing the value of a tile by ++
    int operator++();

private:
    // Value of the tile
    int mValue = 0;

    // States if tile is hidden or not
    int mHidden = true;

    // States if tile is flagged or not
    int mFlag = false;
};
