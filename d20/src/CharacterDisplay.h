#pragma once
#include "Tile.h"
#include "TextField.h"
#include "GameResource.h"
#include "Character.h"
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(CharacterDisplay, spCharacterDisplay);

//This class is for the Play option
class CharacterDisplay : public Actor, Observer {
public:
	CharacterDisplay(spCharacter character);
	~CharacterDisplay();

	void setEmptyDisplay();

	void displayStats();

	void setHelm(spTile t);
	void setArmor(spTile t);
	void setBoots(spTile t);
	void setWeapon(spTile t);
	void setShield(spTile t);
	void setRing(spTile t);
	void setBelt(spTile t);

	void refresh();
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
