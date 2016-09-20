#include "Tile.h"
#include "ImageResource.h"

Tile::Tile(std::string image) {
	setSize(TILE_SIZE, TILE_SIZE);
	setImage(image);
}

Tile::~Tile() {

}

void Tile::setImage(std::string imageName, int col, int row) {
	setResAnim(res::resources.getResAnim(imageName), col, row);
}