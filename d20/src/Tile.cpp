#include <iostream>
#include "Tile.h"
#include "ImageResource.h"

Tile::Tile(std::string image, int img_row, int img_col) {
	setSize(TILE_SIZE, TILE_SIZE);
	setImage(image, img_row, img_col);
	setName(image);
}

Tile::Tile(const spTile tile) {
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

bool Tile::operator==(const Tile& other) const {
	return	this->getResAnim() == other.getResAnim() &&
		this->getColumn() == other.getColumn() &&
		this->getRow() == other.getRow();
}

bool Tile::operator!=(const Tile& other) const {
	return !(*this == other);
}