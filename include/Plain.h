#ifndef GAMEOFLIFE_PLAIN_H
#define GAMEOFLIFE_PLAIN_H

#include "Tile.h"
#include <map>

class Plain {

	public:
		explicit Plain(const std::string& filename);
		void render(SDL_Rect& camera) const;
		void play();
		std::vector<Tile> getTileSet() const;
	private:
		// piotrek lox ever the best pies for world lox da
		std::map<int, std::map<int, Tile>> tileSet;
		// methods
		bool setTiles(const std::string& filename);
		bool shouldDie(Tile& tile) const;
		bool shouldDie(int row, int col, bool isEmpty = false) const;
		unsigned int countNeighbours(int row, int col) const;
		void add(int row, int col, char type, bool dirty = true);
		static std::vector<std::pair<int, int>> getNeighbours(int row, int col) ;
};


#endif //GAMEOFLIFE_PLAIN_H
