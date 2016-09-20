#pragma once

#include "oxygine-framework.h"
#include "Tile.h"
using namespace oxygine;

class Grid : public Actor {
	public:
		Grid(int, int);
		~Grid();
		Vector2 getTileOf(spActor);
		spTile getTile(int, int);
		void addToGrid(spActor, int, int);
		void setTile(int, int, spTile);
protected:
	int cols;
	int rows;
	std::vector<std::vector<spTile>> tiles;
};
typedef oxygine::intrusive_ptr<Grid>spGrid;