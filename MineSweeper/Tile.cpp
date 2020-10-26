#include "Tile.h"

int Tile::getValue() {
	return this->mValue;
}

void Tile::setValue(int value) {
	this->mValue = value;
}

void Tile::setBomb() {
	this->mValue = -1;
}

void Tile::setFlag() {
	this->mFlag = !mFlag;
}

void Tile::reveal() {
	this->mHidden = false;
}

void Tile::hide() {
	this->mHidden = true;
}

bool Tile::isBomb() {
	return this->mValue == -1 ? true : false;
}

bool Tile::isFlagged() {
	return this->mFlag;
}

bool Tile::isHidden() {
    return mHidden;
}

int Tile::operator++() {
	this->mValue++;

	return mValue;
}
