#pragma once
#pragma once
#include "Xml.h"
#include "Character.h"
#include "Npc.h"

using namespace std;
using namespace tinyxml2;

class XmlNpc : public Xml {

public:
	XmlNpc();
	int createXml();
	int addToRoot(
		string charClass,
		string charName,
		int level,
		int maxHP,
		int currHP,
		int strength,
		int constitution,
		int dexterity,
		int intelligence,
		int wisdom,
		int charisma,
		int equipmentID,
		int inventoryID,
		bool hostile,
		string talk);
	int addToRoot(Npc&);
	Npc& createNpc(int id);
	const string tags[15] = {
		"Class",
		"Name",
		"Level",
		"MaxHP" ,
		"CurrentHP" ,
		"Strength",
		"Constitution",
		"Dexterity",
		"Intelligence",
		"Wisdom",
		"Charisma" ,
		"EquipmentID",
		"InventoryID",
		"Hostile",
		"Talk"
	};
};