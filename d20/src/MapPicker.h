#pragma once
#include "Layout.h"
#include "MapDao.h"

class MapPicker : public Layout{
public:
	MapPicker();
	~MapPicker();
private:
	spMap map;
	MapDao* dao;
	spTextField highlight;
	void onSelect(Event*);
};