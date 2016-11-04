#pragma once
#include "oxygine-framework.h"
#include "Tile.h"
#include "Grid.h"
using namespace oxygine;

//contains the functionality of a game map
class Map : public Grid {
public:
	Map(int = 20, int = 30);
	~Map();
	Vector2 getEntryPoint();
	void move(spActor, int, int, timeMS = 200);
private:
	Vector2 entry;
};
typedef oxygine::intrusive_ptr<Map>spMap;