#pragma once

#include "LTexture.h"

extern LTexture organism_texture1;
extern LTexture organism_texture2;

class Tile {
	public:
		explicit Tile(int x, int y, char tileType, bool dirty);

		void render(SDL_Rect &camera) const;
		[[nodiscard]] int getRow() const;
		[[nodiscard]] int getCol() const;
		[[nodiscard]] bool isAlive() const;
		void live();
		void die();
		void setDirty(bool d);
		bool toDelete() const;

	private:
		SDL_Rect mBox{};
		char mType;
		int row;
		int col;
		bool dirty;
};