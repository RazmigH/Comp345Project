#pragma once

#include "Layout.h"
#include "Tile.h"
#include "Map.h"
#include "Map.h"
#include "CharacterDisplay.h"
#include "CharacterPicker.h"
#include "InventoryDisplay.h"
#include "GamePicker.h"
#include "MainMenu.h" 

using namespace std;

//This class is for the Play option
DECLARE_SMART(Play, spPlay);
class Play : public Layout {
public:
	Play();
	~Play();
	Play(spGamePicker);

	void init();
	void update();
	void onKeyDown(Event*);
private:
	spGamePicker gamePicker;
	spMap map;
	spCharacter character;
	spCharacterDisplay sc;

	bool once;//! makes sure a key command is not spammed
};