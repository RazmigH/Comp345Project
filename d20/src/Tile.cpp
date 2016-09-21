#include "Tile.h"
#include "ImageResource.h"

Tile::Tile(std::string image, bool solid) : solid(solid){
	setSize(TILE_SIZE, TILE_SIZE);
	setImage(image);
}

Tile::~Tile() {

}

void Tile::setImage(std::string imageName, int col, int row) {
	setResAnim(res::resources.getResAnim(imageName), col, row);
}

void Tile::isSolid(bool solid) {
	this->solid = solid;
}

bool Tile::isSolid() {
	return solid;
}
