#pragma once

#include "oxygine-framework.h"

using namespace oxygine;

class Tile : public Sprite {
public:
	Tile(std::string = "blank");
	~Tile();
	static const int TILE_SIZE = 32;
	void setImage(std::string, int = 0, int = 0);
private:
};
typedef oxygine::intrusive_ptr<Tile>spTile;
