#include "Grid.h"

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
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

Vector2 Grid::getTileOf(spActor actor) {
	int col = actor->getPosition().x / Tile::TILE_SIZE;
	int row = actor->getPosition().y / Tile::TILE_SIZE;

	return Vector2(row, col);
}

void Grid::addToGrid(spActor actor, int row, int col) {
	actor->setPosition(tiles[row][col]->getPosition());

	addChild(actor);
};

void Grid::setTile(int row, int col, spTile tile) {
	tiles[row][col] = tile;
}; 

spTile Grid::getTile(int row, int col) {
	return tiles[row][col];
};
