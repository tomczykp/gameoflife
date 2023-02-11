#include "../include/Plain.h"

bool Plain::setTiles(const std::string &filename) {
	int x = 0, y = 0;

	std::ifstream map(filename);

	if (map.fail()) {
		std::cout << "Unable to load map file!\n";
		return false;
	}

	std::string Line;
	while (std::getline(map, Line)) {
		for (char c: Line) {
			if (c != ' ') {
				this->add(y, x, c, false);
			}
			x++;
		}
		y++;
		x = 0;
	}

	map.close();

	return true;
}

Plain::Plain(const std::string &filename) {
	this->setTiles(filename);
}

void Plain::render(SDL_Rect &camera) const {
	for (Tile tile: this->getTileSet()) {
		tile.render(camera);
	}
}

void Plain::play() {
	std::map<std::pair<int, int>, bool> checked;
	std::vector<Tile> toRemove;

	for (Tile tile: this->getTileSet()) {
		std::vector<std::pair<int, int>> neighbours = Plain::getNeighbours(tile.getRow(), tile.getCol());
		for (auto const& n: neighbours) {
			try {
				tileSet.at(n.first).at(n.second);
			} catch (std::out_of_range& e ) {
				if (!checked.find(n)->second) {
					if (!shouldDie(n.first, n.second, true)) {
						this->add(n.first, n.second, TILE_CHAR_1);
						checked.insert({n, true});
					}
				}
			}
		}
		if (this->shouldDie(tile)) {
			tile.die();
			toRemove.push_back(tile);
		} else {
			tile.live();
		}
		checked.insert({{tile.getRow(), tile.getCol()}, true});

	}

	for (auto& row: this->tileSet) {
		for (auto& col : row.second) {
			col.second.setDirty(false);
		}
	}
	for (Tile& tile: toRemove)
		tileSet.at(tile.getRow()).erase(tile.getCol());
}

unsigned int Plain::countNeighbours(int row, int col) const {
	std::vector<std::pair<int, int>> neighbours = Plain::getNeighbours(row, col);

	unsigned int count = 0;
	for (std::pair<int,int> const& ti : neighbours) {
		try {
			Tile neighbour = tileSet.at(ti.first).at(ti.second);
			if (neighbour.isAlive())
				count++;
		}
		catch (std::out_of_range& e) {}

	}
	return count;
}

bool Plain::shouldDie(Tile &tile) const {
	return this->shouldDie(tile.getRow(), tile.getCol());
}

bool Plain::shouldDie(int row, int col, bool isEmpty) const {
	unsigned int c = this->countNeighbours(row, col);
	if (isEmpty)
		return c != 3;
	return !(c == 2 || c == 3);
}


std::vector<Tile> Plain::getTileSet() const {
	std::vector<Tile> vectorTile;
	for (auto const& row: this->tileSet) {
		for (auto const& col : row.second) {
			vectorTile.push_back(col.second);
		}
	}
	return vectorTile;
}

void Plain::add(int row, int col, char type, bool dirty) {
	auto const& value = std::pair<int, Tile>(col, Tile(col, row, type, dirty));
	try {
		this->tileSet.at(row).insert(value);
	} catch (std::out_of_range& e) {
		try {
			this->tileSet.insert({row, std::map<int, Tile>()});
			this->tileSet.at(row).insert(value);
		} catch (std::out_of_range& e) {
			std::cout << "ERROR: failed to add row map into cols map\n";
		}
	}
}

std::vector<std::pair<int, int>> Plain::getNeighbours(int row, int col) {
	return {
			std::pair(row-1, col-1),
			std::pair(row-1, col),
			std::pair(row-1, col+1),
			std::pair(row, col-1),
			std::pair(row, col+1),
			std::pair(row+1, col-1),
			std::pair(row+1, col),
			std::pair(row+1, col+1)
	};
}

