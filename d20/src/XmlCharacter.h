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
	int addToRoot(string charClass, string charName, int level, int strength, 
		int constitution, int dexterity, int intelligence, int wisdom, int charisma);
	int addToRoot(Fighter&);
	Fighter& createCharacter(int id);
	const string tags[9] = { "Class", "Name", "Level", "Strength", "Constitution", "Dexterity", "Intelligence",
		"Wisdom", "Charisma" };
};