#include <random>
#include "include/Tile.h"
#include "include/global.h"
#include "include/View.h"
#include "include/Plain.h"

bool init();
bool loadMedia();
void close();
bool generateMap(const std::string& filename);
bool randomMap = false;

/*
 *  Game of life implementation using SDL2 in C++
 *  Press space to move forward one-step
 *  Map is auto generate with uniform distribution
 *  or can be predefined (change randomMap variable) (then res/initial.map file contains loaded map)
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
	if (!init()) {
		std::cout << "Failed to initialize!\n";
	} else {

		if (!loadMedia()) {
			std::cout << "Failed to load media!\n";
		} else {

			// Event handler
			SDL_Event e;
			SDL_Rect camera = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT};
			bool forward = false;
			std::string mapName = "initial.map";
			if (randomMap) {
				mapName = "random.map";
				if (!generateMap(mapName)) {
					std::cout << "Failed to generate map\n";
					return -1;
				}
			}
			auto* plain = new Plain(res + mapName);
			auto* view = new View(1, 1);

			// Main loop flag
			bool quit = false;
			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {

					if (e.type == SDL_QUIT) {
						quit = true;
					}

					if (e.key.keysym.sym == SDLK_SPACE)
						forward = e.type == SDL_KEYDOWN;

					view->handleEvent(e);

				}

				view->setCamera(camera);
				if (forward) {
					plain->play();
					forward = false;
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// render things
				plain->render(camera);

				// use renderer
				SDL_RenderPresent(gRenderer);
			}
		}

		// Free resources and close SDL
		close();
	}

	return 0;
}

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout <<  "SDL could not initialize! SDL Error: %s\n" << SDL_GetError() << "\n";
		success = false;
	} else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			std::cout << "Warning: Linear texture filtering not enabled!\n";
		}

		gWindow = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED,
		                           SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
		                           SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
		if (gWindow == nullptr) {
			std::cout <<
				"Window could not be created! SDL Error: %s\n"
				<< SDL_GetError() << "\n";
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(
					gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr) {
				std::cout
					<< "Renderer could not be created! SDL Error: %s\n"
					<< SDL_GetError() << "\n";
				success = false;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout
						<< "SDL_image could not initialize! SDL_image Error: %s\n"
						<< IMG_GetError() << "\n";
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia() {

	if (!organism_texture1.loadFromFile(res + "life0.png")) {
		std::cout << "Failed to load tile set texture!\n";
		return false;
	}

	if (!organism_texture2.loadFromFile(res + "life1.png")) {
		std::cout << "Failed to load tile set texture!\n";
		return false;
	}

	return true;
}

void close() {

	organism_texture2.free();
	organism_texture1.free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}


bool generateMap(const std::string& filename) {

	std::ofstream map((res + filename).c_str());
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniformMapRange(20, 50);

	if (map.fail()) {
		std::cout << "Unable to load map file!\n";
		return false;
	}

	const int rows = uniformMapRange(e1);
	const int cols = uniformMapRange(e1);

	std::uniform_int_distribution<int> uniform_dist(1, 6);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			char elem = ' ';
			if (uniform_dist(e1) == 1)
				elem = '#';
			map << elem;
		}
		map << "\n";
	}

	map.close();

	return true;


}