#pragma once

#include "oxygine-framework.h"
#include "Tile.h"
using namespace oxygine;

//this class generates and provides options to manipulate a grid
//made of equal-sized cells
class Grid : public Actor {
	public:
		Grid(int, int);
		~Grid();
		Vector2 getTileLocation(spActor);
		Vector2 getTileLocation(Vector2);
		spTile getTile(int, int);
		spTile getTile(Vector2);
		void addToGrid(spActor, int, int);
		void setTile(int, int, spTile);
		void setTile(Vector2, spTile);
protected:
	int cols;
	int rows;
	std::vector<std::vector<spTile>> tiles;
};
typedef oxygine::intrusive_ptr<Grid>spGrid;