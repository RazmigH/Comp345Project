#pragma once
#include "Tile.h"
#include "TextField.h"
#include "GameResource.h"
#include "Character.h"
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(CharacterDisplay, spCharacterDisplay);

//This class is for the Play option
class CharacterDisplay : public Actor {
public:
	CharacterDisplay();
	CharacterDisplay(spCharacter character);
	~CharacterDisplay();

	void setEmptyDisplay();

	void displayStats();

	void setHelm(Tile t);
	void setArmor(Tile t);
	void setBoots(Tile t);
	void setWeapon(Tile t);
	void setShield(Tile t);
	void setRing(Tile t);
	void setBelt(Tile t);
private:
	Resources res;
	spTile helm;
	spTile armor;
	spTile boots;
	spTile weapon;
	spTile shield;
	spTile ring;
	spTile belt;
	spCharacter character;
};
