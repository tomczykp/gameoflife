#ifndef GAMEOFLIFE_GLOBAL_H
#define GAMEOFLIFE_GLOBAL_H

#include <SDL.h>
#include <SDL_image.h>

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

const int TILE_WIDTH = 10;
const int TILE_HEIGHT = 10;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 480;
const char TILE_CHAR_1 = '#';
const char TILE_CHAR_2 = '@';
const char TILE_CHAR_EMPTY = ' ';

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

const std::string res = "../res/";


#endif //GAMEOFLIFE_GLOBAL_H
