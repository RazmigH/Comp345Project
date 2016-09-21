#include "Tile.h"
#include "ImageResource.h"

Tile::Tile(std::string image, bool solid, int img_row, int img_col) : solid(solid) {
	setSize(TILE_SIZE, TILE_SIZE);
	setImage(image, img_row, img_col);
	setName(image);
}

Tile::Tile(const spTile tile) : solid(tile->solid) {
	setSize(tile->getSize());
	setImage(tile->getResAnim(), tile->getColumn(), tile->getRow());
	setName(tile->getName());
}

Tile::~Tile() {

}

void Tile::setImage(const ResAnim* resAnim, int col, int row) {
	setResAnim(resAnim, col, row);
}
void Tile::setImage(std::string imageName, int col, int row) {
	setImage(res::resources.getResAnim(imageName), col, row);
}

//sets ability to move to through tile
void Tile::isSolid(bool solid) {
	this->solid = solid;
}

bool Tile::isSolid() {
	return solid;
}
