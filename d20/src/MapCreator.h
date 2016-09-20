#pragma once

#include "Layout.h"
using namespace std;

class MapCreator : public Layout {
public:
	MapCreator();
	~MapCreator();
private:
};
typedef oxygine::intrusive_ptr<MapCreator>spMapCreator;