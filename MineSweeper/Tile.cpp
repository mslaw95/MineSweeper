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

bool Tile::isBomb() {
	return this->mValue == -1 ? true : false;
}

bool Tile::isHidden() {
    return mHidden;
}

int Tile::operator++() {
	this->mValue++;

	return mValue;
}