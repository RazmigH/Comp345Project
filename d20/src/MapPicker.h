#pragma once
#include "Layout.h"
#include "MapDao.h"
#include "TextButton.h"

DECLARE_SMART(MapPicker, spMapPicker);
class MapPicker : public Layout{
public:
	MapPicker();
	~MapPicker();

	spMap getMap();

	void init();
private:
	spMap map;
	MapDao* dao;
	spTextField highlight;
	spTextButton okbtn;
	void onSelect(Event*);
	void load();
};