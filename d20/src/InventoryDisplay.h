#pragma once
#include "Tile.h"
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(InventoryDisplay, spInventoryDisplay);

//This class is for the Play option
class InventoryDisplay : public Actor {
public:
	InventoryDisplay();
	~InventoryDisplay();

	void setEmptyInventory();
	void setInventoryDisplaySlot(spTile, int, int);
private:
	spTile items[4][3];
	int inventorySlots = 12;
	int rows = 4;
	int cols = 3;
};
