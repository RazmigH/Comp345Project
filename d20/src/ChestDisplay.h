#pragma once
#include "Layout.h"
#include "Chest.h"
#include "DynamicGrid.h"
#include "TextButton.h"
#include "Character.h"

DECLARE_SMART(ChestDisplay, spChestDisplay);
class ChestDisplay : public Layout {
public:
	ChestDisplay(spChest);
	~ChestDisplay();

	void onSelectItem(Event*);
	void init();
	void update();
private:
	void load();
	spCharacter character;
	spChest chest;
	spTextField title;
};