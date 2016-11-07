#include <iostream>
#include "Map.h"

Map::Map(int rows, int cols) : Grid(rows, cols) {
	//set default entry to bottom middle of map
	//entry = Vector2(rows - 1, cols / 2);
}

Map::~Map() {

}

spTile Map::getEntryPoint() {
	return NULL;
}

//moves a tile to provided location with a transition lasting "duration" milliseconds
void Map::move(spActor actor, int row, int col, timeMS duration) {
	//outer bounds check, dont move if attempting to move out of map
	if (row >= rows || row < 0 || col >= cols || col < 0) {
		std::cout << "Cant move '" << actor->getObjectID() << "' to " << row << "x" << col << " : Out of bounds" << std::endl;
	}
	else {
		//new tile we are moving to exists
		Tile rawtile = tiles[row][col];
		spMapTile tile = dynamic_cast<MapTile*>(&rawtile);

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