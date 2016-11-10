#pragma once

#include "Layout.h"
#include "Tile.h"
#include "Map.h"
#include "Map.h"
#include "CharacterDisplay.h"
#include "CharacterPicker.h"
#include "InventoryDisplay.h"
#include "MainMenu.h" 

using namespace std;

//This class is for the Play option
DECLARE_SMART(Play, spPlay);
class Play : public Layout {
public:
	Play();
	~Play();
	Play(spCharacterPicker useCharacter);

	void init();
private:
	spMap map;
	spCharacter character;

};