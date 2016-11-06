#pragma once
#include "Xml.h"
#include "Character.h"
#include "Fighter.h"

using namespace std;
using namespace tinyxml2;

class XmlCharacter : public Xml {

public:
	XmlCharacter();
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
		int inventoryID);
	int addToRoot(Fighter&);
	Fighter& createCharacter(int id);
	const string tags[13] = { 
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
		"InventoryID" 
	};
};