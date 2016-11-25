#pragma once
#include "Tile.h"
#include "oxygine-framework.h"
#include "DynamicGrid.h"
#include "Observer.h"
#include "Character.h"

using namespace oxygine;

DECLARE_SMART(InventoryDisplay, spInventoryDisplay);

//This class is for the Play option
class InventoryDisplay : public Actor, Observer {
public:
	InventoryDisplay(spCharacter);
	~InventoryDisplay();

	void refresh();
	void update(const UpdateState& us);
private:
	spDynamicGrid inventoryGrid;
	spCharacter character;
	spTextField title;
	spGrid background;

	void onInventoryClick(Event*);
};
