#include <iostream>
#include "Grid.h"

Grid::Grid(int cols, int rows) : rows(rows), cols(cols) {
	//set vector sizes
	tiles.resize(rows);
	for (int i = 0; i < rows; ++i) {
		tiles.at(i).resize(cols);
	}

	//set grid size depending on amount of rows/cols (using TILE_SIZE)
	this->setSize(Vector2(Tile::TILE_SIZE * cols, Tile::TILE_SIZE * rows));

	//initialize the tiles
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			tiles[row][col] = new Tile();
			tiles[row][col]->setPosition(Tile::TILE_SIZE * col, Tile::TILE_SIZE * row);
			addChild(tiles[row][col]);
		}
	}
}

Grid::~Grid() {

}

//returns the tile location row/col of the provided coordinates
Vector2 Grid::getTileLocation(Vector2 position) {
	int row = position.y / Tile::TILE_SIZE;
	int col = position.x / Tile::TILE_SIZE;
	return Vector2(col, row);
}

Vector2 Grid::getTileLocation(spActor actor) {
	return getTileLocation(actor->getPosition());
}

//adds an actor to the grid
//the actor remains untracked / independent of the grid
void Grid::addToGrid(spActor actor, int col, int row) {
	actor->setPosition(tiles[row][col]->getPosition());

	addChild(actor);
};

//replaces a tile with the provided one
void Grid::setTile(int col, int row, spTile tile) {
	std::cout << "Setting tile " << col << "x" << row << " to : " << tile->getName() << std::endl;
	removeChild(tiles[row][col]);
	tile->setPosition(Tile::TILE_SIZE * col, Tile::TILE_SIZE * row);
	tiles[row][col] = tile;
	addChild(tiles[row][col]);
};
void Grid::setTile(Vector2 loc, spTile tile) {
	setTile(loc.x, loc.y, tile);
};
void Grid::setTiles(spTile tile) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			setTile(c, r, tile->clone());
		}
	}
}

//returns the tile at the provided location
spTile Grid::getTile(int col, int row) {
	return tiles[row][col];
};
spTile Grid::getTile(Vector2 loc) {
	return getTile(loc.x, loc.y);
};

int Grid::getCols() {
	return cols;
}

int Grid::getRows() {
	return rows;
}