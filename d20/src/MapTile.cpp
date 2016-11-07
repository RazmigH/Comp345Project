#include "MapTile.h"
#include "DefaultEditPane.h"

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

spActor MapTile::getEditLayout(){
	spDefaultEditPane actor = new DefaultEditPane(this);
	return actor;
};

bool MapTile::isEntryTile() {
	return isEntry;
}

bool MapTile::isFinishTile() {
	return isFinish;
}

void MapTile::isEntryTile(bool b) {
	isEntry = b;
}

void MapTile::isFinishTile(bool b) {
	isFinish = b;
}