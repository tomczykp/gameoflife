#include "../include/Tile.h"

LTexture organism_texture1;
LTexture organism_texture2;

void Tile::render(SDL_Rect &camera) const {
	const int nx = mBox.x - camera.x;
	const int ny = mBox.y - camera.y;

	switch (mType) {
		case TILE_CHAR_1:
			organism_texture1.render(nx,ny);
			break;

		case TILE_CHAR_2:
			organism_texture2.render(nx,ny);
			break;
		default:
			break;
	}
}

Tile::Tile(int x, int y, char tileType, bool d) {
	mBox.x = x * TILE_WIDTH;
	mBox.y = y * TILE_HEIGHT;
	row = y;
	col = x;
	this->dirty = d;

	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	mType = tileType;
}

int Tile::getRow() const {
	return row;
}

int Tile::getCol() const {
	return col;
}

void Tile::die() {
	this->mType = TILE_CHAR_EMPTY;
}

void Tile::live() {
	this->mType = TILE_CHAR_1;
}

bool Tile::isAlive() const {
	return !dirty;
}

void Tile::setDirty(bool isDirty) {
	Tile::dirty = isDirty;
}

bool Tile::toDelete() const {
	return mType == TILE_CHAR_EMPTY;
}
