#pragma once

class Tile {
public:
    bool isBomb();
    bool isHidden();

	int getValue();
	void setValue(int value);
    void setBomb();

    int operator++();

private:
    int mValue = 0;
    int mHidden = true;
};
