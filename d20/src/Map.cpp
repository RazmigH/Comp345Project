#include <iostream>
#include "Map.h"

Map::Map(int rows, int cols) : Grid(rows, cols) {
	entry = Vector2(rows - 1, cols / 2);
}

Map::~Map() {

}

Vector2 Map::getEntryPoint() {
	return entry;
}

void Map::move(spActor actor, int row, int col, timeMS duration) {
	if (row >= rows || row < 0 || col >= cols || col < 0) {
		std::cout << "Cant move '" << actor->getObjectID() << "' to " << row << "x" << col << " : Out of bounds" << std::endl;
	}
	else {
		//new tile exists
		spTile tile = tiles[row][col];
		if (tile->isSolid()) {
			std::cout << "Cant move '" << actor->getObjectID() << "' to " << row << "x" << col << " : Tile is Solid" << std::endl;
		}
		else {
			//actor->setPosition(tile->getPosition());
			//spTweenQueue tQueue = new TweenQueue();
			//tQueue->add();
			if (actor->getFirstTween() == NULL) {
				std::cout << "Moving '" << actor->getObjectID() << "' to " << row << "x" << col << std::endl;

				actor->addTween(Sprite::TweenPosition(tile->getPosition()), duration);
			}
		}
	}
}