
#include "XmlCharacter.h"

XmlCharacter::XmlCharacter() : Xml("Characters.xml", 9) {
}

//! createXml() -> creates an XML file and adds the root to it
int XmlCharacter::createXml() {
	Xml::createXml("Characters");

	return 0;
}

//! addToRoot(params) -> adds a new character's parameters to the Xml file
int XmlCharacter::addToRoot(string charClass, string charName, int level, int strength, int constitution,
	int dexterity, int intelligence, int wisdom, int charisma) {
	if (isEmpty()) {
		createXml();
	}
	const string attrs[] = { charClass, charName, to_string(level), to_string(strength), to_string(constitution),
		to_string(dexterity), to_string(intelligence), to_string(wisdom), to_string(charisma) };
	return Xml::addToRoot("Character", tags, attrs);
}

//! addToRoot(Fighter) -> adds to 
int XmlCharacter::addToRoot(Fighter& c) {
	if (isEmpty()) {
		createXml();
	}
	const string attrs[] = { c.getCharacterClass() , c.getName(), to_string(c.getLevel()), to_string(c.getStat(STR)), 
		to_string(c.getStat(CON)), to_string(c.getStat(DEX)), to_string(c.getStat(INT)), to_string(c.getStat(WIS)), 
		to_string(c.getStat(CHA)) };
	return Xml::addToRoot("Character", tags, attrs);
	return 0;
}

//! createCharacter(id) -> builds a character that has the give id,  by using the character parameters from the xml file
Fighter& XmlCharacter::createCharacter(int id) {
	vector<string> charParams = readDataByID(id);
	//! CAREFULL: that part needs an allocation on the heap
	//! Assuming it's only a fighter class that can be found, because it's the only one implemented
	Fighter* builder = new Fighter(charParams.at(1), stoi(charParams.at(2)),
		stoi(charParams.at(3)), stoi(charParams.at(4)), stoi(charParams.at(5)), 
		stoi(charParams.at(6)), stoi(charParams.at(7)), stoi(charParams.at(8)));
	return *builder;
}