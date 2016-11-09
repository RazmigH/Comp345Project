#pragma once

#include "Layout.h"
#include "Tile.h"
#include "Map.h"
using namespace std;

//This class is for the Play option
class Play : public Layout {
public:
	Play();
	~Play();
private:
	spMap map;

};