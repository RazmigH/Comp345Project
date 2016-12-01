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

	vector<spItem> getItems();

	//void onSelectItem(Event*);
	void init();
	void update();

	void onSelectItem(Event*);
private:
	void refreshItems();
	bool isSelected(spItem);
	void addSelected(spItem);
	void removeSelected(spItem);

	spCharacter character;
	spChest chest;

	spTextField title;
	spTextButton okbtn;
	spDynamicGrid grid;
	spColorRectSprite highlight;
	vector<vector<spColorRectSprite>> highlights;

	vector<spItem> selected;
};