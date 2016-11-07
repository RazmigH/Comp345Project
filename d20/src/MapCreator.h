#pragma once

#include "Layout.h"
#include "Tile.h"
#include "Map.h"
using namespace std;

//This class is for the map creation window / layout
class MapCreator : public Layout {
public:
	enum CreatorAction {
		SELECT, TILE_EDIT
	};
	MapCreator();
	~MapCreator();
private:
	spTile selected;
	void onSelectTileOption(Event*);
	void onSelectToolClicked(Event*);
	void onSelectMapTile(Event*);
	void onMoveOnMap(Event*);
	void fill(Event*);
	spMap map;
	spGrid selections;
	CreatorAction currentAction;
	spTextField detailsTitle;
	spActor detailsPane;
	spActor currentDetails;
};
typedef oxygine::intrusive_ptr<MapCreator>spMapCreator;