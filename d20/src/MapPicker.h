#pragma once
#include "Layout.h"
#include "TextButton.h"
#include "Map.h"

DECLARE_SMART(MapPicker, spMapPicker);
class MapPicker : public Layout{
public:
	MapPicker();
	~MapPicker();

	spMap getMap();
	void setMap(spMap);

	void init();
	void update();
private:
	spTextField highlight;
	vector<spTextField> mapTexts;

	spActor selected;
	string mapId = "";

	spTextButton okbtn;

	void onSelect(Event*);
};