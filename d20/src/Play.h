#pragma once

#include "Layout.h"
#include "Tile.h"
#include "Map.h"
using namespace std;

//This class is for the Play option
DECLARE_SMART(Play, spPlay);
class Play : public Layout {
public:
	Play();
	~Play();

	void init();
private:
	spMap map;

};