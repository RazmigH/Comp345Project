#pragma once
#include "CharacterPicker.h"
#include "MapPicker.h"
#include "TextButton.h"

DECLARE_SMART(GamePicker, spGamePicker);
class GamePicker : public Layout {
public:
	GamePicker();
	~GamePicker();

	spMap getMap();
	void setMap(spMap);
	spCharacter getCharacter();
	void setCharacter(spCharacter);

	spMapPicker getMapPicker() {
		return mapPicker;
	}

	void init();
private:
	spCharacterPicker characterPicker;
	spMapPicker mapPicker;

	spTextButton mapBtn;
	spTextButton charBtn;
	spTextButton okbtn;
	spTextField mapText;
	spTextField characterText;

	
};