#pragma once
#include "Xml.h"

using namespace std;
using namespace tinyxml2;

class XmlCharacter : public Xml {

public:
	XmlCharacter();
	int createXml();
	int addToRoot(string charClass, string charName, int strength, int constitution,
		int dexterity, int intelligence, int wisdom, int charisma);

};