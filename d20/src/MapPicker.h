#pragma once
#include "Layout.h"
#include "MapDao.h"
#include "TextButton.h"

class MapPicker : public Layout{
public:
	MapPicker();
	~MapPicker();
private:
	spMap map;
	MapDao* dao;
	spTextField highlight;
	spTextButton okbtn;
	void onSelect(Event*);
	void load();
};