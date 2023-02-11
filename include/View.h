#ifndef GAMEOFLIFE_VIEW_H
#define GAMEOFLIFE_VIEW_H

#include "global.h"

class View {
	public:
		const float VEL = 2.0f;

		explicit View(int x = 0, int y = 0);

		void handleEvent(SDL_Event &e);
		void setCamera(SDL_Rect &camera);

	private:
		SDL_Rect mBox;
		float mVelx, mVely;
		void move();
};


#endif //GAMEOFLIFE_VIEW_H
