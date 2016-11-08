#include <iostream>
#include "Map.h"

Map::Map(int rows, int cols) : Grid(rows, cols) {
	entryHighlight = new ColorRectSprite();
	entryHighlight->setSize(Tile::TILE_SIZE, Tile::TILE_SIZE);
	entryHighlight->setColor(Color::LimeGreen);
	entryHighlight->setAlpha(50000);
	//addToGrid(entryHighlight, getEntryPoint().x, getEntryPoint().y);

	exitHighlight = new ColorRectSprite();
	exitHighlight->setSize(Tile::TILE_SIZE, Tile::TILE_SIZE);
	exitHighlight->setColor(Color::YellowGreen);
	exitHighlight->setAlpha(50000);
	//addToGrid(exitHighlight, getExitPoint().x, getExitPoint().y);

	id = -1;
}

Map::~Map() {

}

Vector2 Map::getEntryPoint() {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			spTile tile = tiles[row][col];
			if (tile->isEntryTile()) {
				return this->getTileLocation(tile);
			}
		}
	}
	return Vector2(rows - 1, cols / 2);
}

Vector2 Map::getExitPoint() {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			spTile tile = tiles[row][col];
			if (tile->isFinishTile()) {
				return this->getTileLocation(tile);
			}
		}
	}
	return Vector2(0, cols / 2);
}

//moves a tile to provided location with a transition lasting "duration" milliseconds
void Map::move(spActor actor, int row, int col, timeMS duration) {
	//outer bounds check, dont move if attempting to move out of map
	if (row >= rows || row < 0 || col >= cols || col < 0) {
		std::cout << "Cant move '" << actor->getObjectID() << "' to " << row << "x" << col << " : Out of bounds" << std::endl;
	}
	else {
		//new tile we are moving to exists
		spTile tile = tiles[row][col];

		//dont move if tile is solid
		if (tile->isSolid()) {
			std::cout << "Cant move '" << actor->getObjectID() << "' to " << row << "x" << col << " : Tile is Solid" << std::endl;
		}
		else {
			//actor->setPosition(tile->getPosition());
			//spTweenQueue tQueue = new TweenQueue();
			//tQueue->add();

			//smooth transition to new tile
			if (actor->getFirstTween() == NULL) {
				std::cout << "Moving '" << actor->getObjectID() << "' to " << row << "x" << col << std::endl;

				actor->addTween(Sprite::TweenPosition(tile->getPosition()), duration);
			}
		}
	}
}

void Map::render(const RenderState &rs) {
	Grid::render(rs);
	addToGrid(entryHighlight, getEntryPoint().x, getEntryPoint().y);
	addToGrid(exitHighlight, getExitPoint().x, getExitPoint().y);
	//entryHighlight->render(rs);
	//exitHighlight->render(rs);
	//std::cout << "yo" << std::endl;
}

int Map::getId() {
	return id;
}

void Map::setId(int id) {
	this->id = id;
}