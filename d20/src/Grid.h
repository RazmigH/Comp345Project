#pragma once

#include "oxygine-framework.h"
#include "Tile.h"
using namespace oxygine;

//this class generates and provides options to manipulate a grid
//made of equal-sized cells
class Grid : public Actor {
public:
	Grid(int rows, int cols);
	~Grid();
	Vector2 getTileLocation(spActor);
	Vector2 getTileLocation(Vector2 position);
	spTile getTile(int row, int col);
	spTile getTile(Vector2);
	void addToGrid(spActor, int row, int col);
	void setTile(int row, int col, spTile);
	void setTile(Vector2, spTile);
	void setTiles(spTile);
	int getCols();
	int getRows();
protected:
	int cols;
	int rows;
	std::vector<std::vector<spTile>> tiles;
};
typedef oxygine::intrusive_ptr<Grid>spGrid;