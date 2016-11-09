#pragma once
#include "Layout.h"
#include "CharacterDao.h"
#include "DynamicGrid.h"
#include "TextButton.h"

class CharacterPicker : public Layout {
public:
	CharacterPicker(string = "Pick a Character");
	~CharacterPicker();
	void onSelectCharacter(Event*);
private:
	CharacterDao* dao;
	void load();
	spDynamicGrid grid;
	spTextButton okbtn;
	spColorRectSprite highlight;
	spTile empty;
	spCharacter character;
	spTextField title;
};