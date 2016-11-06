#include "MapTile.h"

MapTile::MapTile(std::string image, bool solid, int col, int row) : Tile(image, col, row), solid(solid) {

}
MapTile::~MapTile() {

}

//sets ability to move to through tile
void MapTile::isSolid(bool solid) {
	this->solid = solid;
}

bool MapTile::isSolid() {
	return solid;
}