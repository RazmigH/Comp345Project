#pragma once

#include "oxygine-framework.h"

using namespace oxygine;

class Tile : public Sprite {
public:
	Tile(std::string = "blank", bool = false);
	~Tile();
	static const int TILE_SIZE = 32;
	void setImage(std::string, int = 0, int = 0);
	bool isSolid();
	void isSolid(bool);
private:
	bool solid;
};
typedef oxygine::intrusive_ptr<Tile>spTile;
