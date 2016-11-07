#pragma once
#include "Tile.h"

DECLARE_SMART(MapTile, spMapTile);
class MapTile : public Tile {
public:
	MapTile(std::string = "blank", bool = false, int = 0, int = 0);
	~MapTile();
	bool isSolid();
	void isSolid(bool);
	spActor getEditLayout();
	spTile clone() {
		spMapTile tile = new MapTile(this->getResAnim()->getName(), this->solid, this->getColumn(), this->getRow());
		return tile;
	}

	bool MapTile::isEntryTile();
	void MapTile::isEntryTile(bool);
	bool MapTile::isFinishTile();
	void MapTile::isFinishTile(bool);
private:
	bool solid;
	bool isEntry = false;
	bool isFinish = false;
};