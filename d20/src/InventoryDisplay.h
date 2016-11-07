#pragma once
#include "Tile.h"
#include "oxygine-framework.h"
#include "Grid.h"

using namespace oxygine;

DECLARE_SMART(InventoryDisplay, spInventoryDisplay);

//This class is for the Play option
class InventoryDisplay : public Actor {
public:
	InventoryDisplay();
	~InventoryDisplay();
	spGrid inventoryGrid;
	void setEmptyInventory();
	void setInventoryDisplaySlot(spTile, int, int);
	void onClickInventorySlot(Event* e );
private:
	spTile items[5][3];
};
