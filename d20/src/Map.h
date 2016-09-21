#pragma once
#include "oxygine-framework.h"
#include "Tile.h"
#include "Grid.h"
using namespace oxygine;

class Map : public Grid {
public:
	Map(int = 10, int = 20);
	~Map();
	Vector2 getEntryPoint();
	void move(spActor, int, int, timeMS = 200);
private:
	Vector2 entry;
};
typedef oxygine::intrusive_ptr<Map>spMap;