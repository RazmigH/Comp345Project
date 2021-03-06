#pragma once

#include "Layout.h"
#include "Tile.h"
#include "Map.h"
#include "MapPicker.h"
#include "EditPane.h"
using namespace std;

//This class is for the map creation window / layout
DECLARE_SMART(MapCreator, spMapCreator);
class MapCreator : public Layout {
public:
	enum CreatorAction {
		SELECT, TILE_EDIT
	};
	MapCreator(spMapPicker);
	~MapCreator();

	void init();
	void update();
private:
	spTile selectedOption;
	spTile selectedTile;
	void onSelectTileOption(Event*);
	void onSelectMapTile(Event*);
	void onMoveOnMap(Event*);
	void fill(Event*);
	void saveMap(Event*);
	void setNextMap(Event*);
	spMap map;
	spGrid selections;
	CreatorAction currentAction;
	spTextField detailsTitle;
	spActor detailsPane;
	spActor currentDetails;
	spColorRectSprite highlight;
	spMapPicker mapSource;

	spActor selectPane;
	spGrid selectGrid;

	spTextButton fillBtn;
	spTextButton save;
	spTextButton nextMap;

	spActor topPane;

	spEditPane getEditPane(spTile);
};