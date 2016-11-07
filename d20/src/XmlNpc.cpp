
#include "XmlNpc.h"

XmlNpc::XmlNpc() : Xml("NPCs.xml", 15) {
}

//! createXml() -> creates an XML file and adds the root to it
int XmlNpc::createXml() {
	Xml::createXml("NPCs");

	return 0;
}

//! addToRoot(params) -> adds a new character's parameters to the Xml file
int XmlNpc::addToRoot(
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
	string talk)
{

	if (isEmpty()) {
		createXml();
	}
	const string attrs[] = {
		charClass,
		charName,
		to_string(level),
		to_string(maxHP),
		to_string(currHP),
		to_string(strength),
		to_string(constitution),
		to_string(dexterity),
		to_string(intelligence),
		to_string(wisdom),
		to_string(charisma),
		to_string(equipmentID),
		to_string(inventoryID),
		to_string(hostile),
		talk
	};
	return Xml::addToRoot("NPC", tags, attrs);
}

//! addToRoot(Fighter) -> adds a Fighter class data to Xml
int XmlNpc::addToRoot(Npc& c) {
	if (isEmpty()) {
		createXml();
	}

	// setting maxHP to currentHP to reset the fight on load
	const string attrs[] = {
		c.getCharacterClass(),
		c.getName(),
		to_string(c.getLevel()),
		to_string(c.getMaxHP()),
		to_string(c.getMaxHP()),
		to_string(c.getStat(STR)),
		to_string(c.getStat(CON)),
		to_string(c.getStat(DEX)),
		to_string(c.getStat(INT)),
		to_string(c.getStat(WIS)),
		to_string(c.getStat(CHA)),
		to_string(c.getEquipID()),
		to_string(c.getInvID()),
		to_string(c.isHostile()),
		c.getTalk()
	};
	return Xml::addToRoot("Character", tags, attrs);
	return 0;
}

//! createNpc(id) -> builds a NPC that has the give id,  by using the parameters from the xml file
Npc& XmlNpc::createNpc(int id) {
	vector<string> charParams = readDataByID(id);
	//! CAREFULL: that part needs an allocation on the heap
	Npc* builder = new Npc(
		charParams.at(1),
		stoi(charParams.at(2)),
		stoi(charParams.at(3)),
		stoi(charParams.at(4)),
		stoi(charParams.at(5)),
		stoi(charParams.at(6)),
		stoi(charParams.at(7)),
		stoi(charParams.at(8)),
		stoi(charParams.at(9)),
		stoi(charParams.at(10)),
		stoi(charParams.at(11)),
		stoi(charParams.at(12)),
		stoi(charParams.at(13)),
		charParams.at(14)
	);

	return *builder;
}