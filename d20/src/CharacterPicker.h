#pragma once
#include "Layout.h"
#include "CharacterDao.h"
#include "DynamicGrid.h"
#include "TextButton.h"

DECLARE_SMART(CharacterPicker, spCharacterPicker);
class CharacterPicker : public Layout {
public:
	CharacterPicker(string = "Pick a Character");
	~CharacterPicker();

	spCharacter getCharacter();

	void onSelectCharacter(Event*);
	void init();
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