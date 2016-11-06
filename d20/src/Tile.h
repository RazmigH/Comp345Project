#pragma once

#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(Tile, spTile);
class Tile : public Sprite {
public:
	Tile(std::string = "blank", int = 0, int = 0);
	Tile(const spTile);
	~Tile();
	static const int TILE_SIZE = 32;
	void setImage(std::string, int = 0, int = 0);
	void setImage(const ResAnim*, int = 0, int = 0);

	bool operator==(const Tile&) const;
	bool operator!=(const Tile&) const;
private:
};
