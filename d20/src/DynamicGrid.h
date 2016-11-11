#pragma once

#include "Grid.h"

DECLARE_SMART(DynamicGrid, spDynamicGrid);
class DynamicGrid : public Grid{//private Grid{
public:
	DynamicGrid(int cols, int rows, spTile empty = new Tile);
	~DynamicGrid();
	bool add(spTile);
	bool remove(spTile);
	spTile get(int col, int row);
	spTile remove(int col, int row);
	void clear();
	spTile getLast();
	bool isEmpty(spTile tile);
private:
	spTile empty;
	spTile last;
};