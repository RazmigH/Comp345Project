#include "DynamicGrid.h"

DynamicGrid::DynamicGrid(int cols, int rows, spTile empty) : Grid(cols, rows), empty(empty){
	setName("Dynamic Grid");
}

DynamicGrid::~DynamicGrid() {

}

bool DynamicGrid::add(spTile tile) {
	for (int row = 0; row < getRows(); row++) {
		for (int col = 0; col < getCols(); col++) {
			spTile temp = get(col, row);
			if (*temp == *empty) {
				setTile(col, row, tile);
				last = tile;
				return true;
			}
		}
	}
	return false;
}

bool DynamicGrid::remove(spTile tile) {
	for (int col = 0; col < getCols(); col++) {
		for (int row = 0; row < getRows(); row++) {
			if (tile == getTile(col, row)) {
				setTile(col, row, empty->clone());
				return true;
			}
		}
	}
	return false;
}

spTile DynamicGrid::get(int col, int row) {
	return getTile(col, row);
}

spTile DynamicGrid::remove(int col, int row) {
	spTile old = get(col, row);
	setTile(col, row, empty->clone());
	return old;
}

void DynamicGrid::clear() {
	for (int col = 0; col < getCols(); col++) {
		for (int row = 0; row < getRows(); row++) {
			remove(col, row);
		}
	}
}

spTile DynamicGrid::getLast() {
	return last;
}