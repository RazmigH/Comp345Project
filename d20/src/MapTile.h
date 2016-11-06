#pragma once
#include "Tile.h"

DECLARE_SMART(MapTile, spMapTile);
class MapTile : public Tile {
public:
	MapTile(std::string = "blank", bool = false, int = 0, int = 0);
	~MapTile();
	bool isSolid();
	void isSolid(bool);
	spActor getEditLayout() {
		spActor actor = new Actor();
		return actor;
	};
	spTile clone() {
		spMapTile tile = new MapTile(this->getResAnim()->getName(), this->solid, this->getColumn(), this->getRow());
		return tile;
	}
private:
	bool solid;
};