#pragma once

#include "oxygine-framework.h"
#include "Tile.h"
#include "TextButton.h"
#include "Map.h"
using namespace oxygine;

DECLARE_SMART(EditPane, spEditPane);
class EditPane : public Actor {
public:
	EditPane(spTile, spMap);
	~EditPane();

	spEntity getEntity();
protected:
	spTile tile;
	spMap map;
};