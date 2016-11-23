#pragma once

#include "oxygine-framework.h"
#include "Tile.h"
using namespace oxygine;

//this class generates and provides options to manipulate a grid
//made of equal-sized cells
DECLARE_SMART(Grid, spGrid);
class Grid : public Actor {
public:
	Grid(int cols, int rows);
	~Grid();
	Vector2 getTileLocation(spActor);
	Vector2 getTileLocation(Vector2 position);
	spTile getTile(int col, int row);
	spTile getTile(Vector2);
	spTile getTile(Event*);
	void addToGrid(spActor, int col, int row);
	void setTile(int col, int row, spTile);
	void setTile(Vector2, spTile);
	void setTiles(spTile);
	int getCols();
	int getRows();
	float getTileWidth();
	float getTileHeight();
	void update(const UpdateState& us);
protected:
	int cols;
	int rows;
	std::vector<std::vector<spTile>> tiles;

	spColorRectSprite highlightRect;
	bool highlight = false;
};