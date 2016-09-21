#pragma once

#include "Layout.h"
#include "Tile.h"
#include "Map.h"
using namespace std;

//This class is for the map creation window / layout
class MapCreator : public Layout {
public:
	MapCreator();
	~MapCreator();
private:
	spTile selected;
	void onSelectTileOption(Event*);
	void onSelectMapTile(Event*);
	void onMoveOnMap(Event*);
	spMap map;
	spGrid selections;
};
typedef oxygine::intrusive_ptr<MapCreator>spMapCreator;