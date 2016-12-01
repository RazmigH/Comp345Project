#pragma once
#include "Tile.h"
#include "TextField.h"
#include "GameResource.h"
#include "Character.h"
#include "oxygine-framework.h"
#include "EquipableItem.h"
#include <string>

using namespace oxygine;

DECLARE_SMART(CharacterDisplay, spCharacterDisplay);

//This class is for the Play option
class CharacterDisplay : public Actor, Observer {
public:
	CharacterDisplay(spCharacter character);
	~CharacterDisplay();

	Vector2 resolvePosition(spEquipableItem);

	void refresh();
	void update(const UpdateState& us);
private:
	spTile helm;
	spTile armor;
	spTile boots;
	spTile weapon;
	spTile shield;
	spTile ring;
	spTile belt;
	spCharacter character;

	spTextField title;
	spGrid grid;
	spGrid background;

	const Vector2 HELM_SLOT = Vector2(1, 0);
	const Vector2 WEAPON_SLOT = Vector2(0, 1);
	const Vector2 BODY_SLOT = Vector2(1, 1);
	const Vector2 SHIELD_SLOT = Vector2(2, 1);
	const Vector2 AMULET_SLOT = Vector2(0, 2);
	const Vector2 BOOTS_SLOT = Vector2(1, 2);
	const Vector2 RING_SLOT = Vector2(2, 2);

	spTextField strText;
	spTextField conText;
	spTextField dexText;
	spTextField intText;
	spTextField wisText;
	spTextField charText;
	
	void onEquipmentClick(Event*);
};
