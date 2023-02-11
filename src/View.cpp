#include "../include/View.h"

void View::setCamera(SDL_Rect &camera) {
	this->move();

	// Center the camera over the dot
	camera.x = mBox.x - SCREEN_WIDTH / 2;
	camera.y = mBox.y - SCREEN_HEIGHT / 2;
}

void View::move() {
	mBox.x += mVelx;
	mBox.y += mVely;
}

void View::handleEvent(SDL_Event &e) {
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// Adjust the velocity
		switch (e.key.keysym.sym) {
			case SDLK_w:
				mVely -= VEL;
				break;
			case SDLK_s:
				mVely += VEL;
				break;
			case SDLK_a:
				mVelx -= VEL;
				break;
			case SDLK_d:
				mVelx += VEL;
				break;
		}
	}
		// If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		// Adjust the velocity
		switch (e.key.keysym.sym) {
			case SDLK_a:
			case SDLK_d:
				mVelx = 0;
				break;
			case SDLK_w:
			case SDLK_s:
				mVely = 0;
				break;
		}
	}
}

View::View(int x, int y) {
	mBox.x = x;
	mBox.y = y;
	mBox.w = SCREEN_WIDTH;
	mBox.h = SCREEN_HEIGHT;
	mVelx = 0;
	mVely = 0;
}