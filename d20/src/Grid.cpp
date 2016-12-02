#include "Grid.h"

Grid::Grid(int cols, int rows) : rows(rows), cols(cols) {
	//set vector sizes
	tiles.resize(rows);
	for (int i = 0; i < rows; ++i) {
		tiles.at(i).resize(cols);
	}

	//initialize the tiles
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			tiles[row][col] = new Tile();
			addChild(tiles[row][col]);
		}
	}
}

Grid::~Grid() {

}

//returns the tile location row/col of the provided coordinates
Vector2 Grid::getTileLocation(Vector2 position) {
	int row = (position.y + (getTileHeight() * 0.05)) / getTileHeight();
	int col = (position.x + (getTileWidth() * 0.05)) / getTileWidth();
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
	//std::cout << "Setting tile " << col << "x" << row << " to : " << tile->getName() << std::endl;
	if (tiles[row][col]->getParent() == this)
		removeChild(tiles[row][col]);
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
	if (col < 0 || col >= cols || row < 0 || row >= rows) {
		return nullptr;
	}
	return tiles[row][col];
};
spTile Grid::getTile(Vector2 loc) {
	return getTile(loc.x, loc.y);
};

spTile Grid::getTile(Event* e) {
	TouchEvent* te = safeCast<TouchEvent*>(e);
	Vector2 clickPosition = te->localPosition;
	Vector2 tilePosition = getTileLocation(clickPosition);
	return getTile(tilePosition);
};

int Grid::getCols() {
	return cols;
}

int Grid::getRows() {
	return rows;
}

void Grid::update(const UpdateState& us) {
	Actor::update(us);
	float tile_width = getTileWidth();
	float tile_height = getTileHeight();

	for (int col = 0; col < cols; col++) {
		for (int row = 0; row < rows; row++) {
			tiles[row][col]->setSize(tile_width, tile_height);
			tiles[row][col]->setPosition(tile_width * col, tile_height * row);
		}
	}
}

float Grid::getTileWidth() {
	return getWidth() / cols;
}
float Grid::getTileHeight() {
	return getHeight() / rows;
}