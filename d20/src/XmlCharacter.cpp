#include "stdafx.h"
#include "XmlCharacter.h"

XmlCharacter::XmlCharacter() : Xml("Characters.xml", 8) {
}

int XmlCharacter::createXml() {
	Xml::createXml("Characters");
	return 0;
}

int XmlCharacter::addToRoot(string charClass, string charName, int strength, int constitution,
	int dexterity, int intelligence, int wisdom, int charisma) {
	const string tags[] = { "Class", "Name", "Strength", "Constitution", "Dexterity", "Intelligence", 
		"Wisdom", "Charisma" };
	const string attrs[] = { charClass, charName, to_string(strength), to_string(constitution),
		to_string(dexterity), to_string(intelligence), to_string(wisdom), to_string(charisma) };
	return Xml::addToRoot("Character", tags, attrs);
}