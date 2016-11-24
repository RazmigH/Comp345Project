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
	void setCharacter(spCharacter);

	void onSelectCharacter(Event*);
	void init();
	void update();
private:
	void load();
	string characterId = "";
	spActor selected;

	spDynamicGrid grid;
	spTextButton okbtn;
	spColorRectSprite highlight;
	spTile empty;
	spTextField title;
};