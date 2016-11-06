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
	virtual spTile clone() {
		spTile tile = new Tile(this->getResAnim()->getName(), this->getColumn(), this->getRow());
		return tile;
	}
	virtual spActor getEditLayout() {
		spActor actor = new Actor();
		return actor;
	};

	bool operator==(const Tile&) const;
	bool operator!=(const Tile&) const;
private:
};
