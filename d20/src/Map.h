#pragma once
#include "oxygine-framework.h"
#include "MapTile.h"
#include "Grid.h"
using namespace oxygine;

//contains the functionality of a game map
class Map : public Grid {
public:
	Map(int = 10, int = 20);
	~Map();
	spTile getEntryPoint();
	void move(spActor, int, int, timeMS = 200);
	void setEntryTile(int col, int row);
	void setFinishTile(int col, int row);

	//problem with this, what if we call with a tile thats not part of the map?
	//void Map::setEntryTile(spTile tile);
private:
	//spTile entry;
	//spTile finish;
};
typedef oxygine::intrusive_ptr<Map>spMap;