#pragma once

#include "global.h"

class LTexture {
public:
	LTexture();

	~LTexture();

	bool loadFromFile(const std::string& path);

	void free();

	void render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0,
	            SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	SDL_Texture *mTexture;

	int mWidth;
	int mHeight;
};