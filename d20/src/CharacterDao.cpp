#include "CharacterDao.h"
#include <iostream>
using namespace std;

CharacterDao::CharacterDao(){
	xml = new Xml("Characters");
}

CharacterDao::~CharacterDao() {
	//xml = nullptr;
	delete(xml);
}

vector<Character*> CharacterDao::getCharacters() {
	vector<Character*> chars;
	vector<XMLElement*> elements = xml->getElements();
	for(std::vector<XMLElement*>::iterator it = elements.begin(); it != elements.end(); ++it) {
		chars.push_back(XmlToCharacter(*it));
	}
	return chars;
}

int CharacterDao::addCharacter(Character* c) {
	return xml->addElement(CharacterToXml(c));
}

Character* CharacterDao::XmlToCharacter(XMLElement* element) {
	Character* c = new Character();

	const char* idstr = element->Attribute("id");
	if (idstr != nullptr) {
		c->setId(atoi(idstr));
	}

	int i;

	XMLElement* temp = element->FirstChildElement("Class");
	if (temp != nullptr) {
		c->setCharacterClass(stringToClass(temp->GetText()));
	}

	temp = element->FirstChildElement("Name");
	if (temp != nullptr) {
		c->setName(c->getName());
	}

	temp = element->FirstChildElement("Level");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setLevel(i);
	}

	temp = element->FirstChildElement("MaxHP");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setMaxHP(i);
	}

	temp = element->FirstChildElement("CurrentHP");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setHP(i);
	}

	temp = element->FirstChildElement("Strength");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setStat(Character::Stats::STR, i);
	}

	temp = element->FirstChildElement("Constitution");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setStat(Character::Stats::CON, i);
	}

	temp = element->FirstChildElement("Dexterity");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setStat(Character::Stats::DEX, i);
	}

	temp = element->FirstChildElement("Intelligence");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setStat(Character::Stats::INT, i);
	}

	temp = element->FirstChildElement("Wisdom");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setStat(Character::Stats::WIS, i);
	}

	temp = element->FirstChildElement("Charisma");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
			c->setStat(Character::Stats::CHA, i);
	}

	temp = element->FirstChildElement("EquipmentID");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setEquipID(i);
	}

	temp = element->FirstChildElement("InventoryID");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setInvID(i);
	}

	temp = element->FirstChildElement("Hostile");
	if (temp != nullptr) {
		c->isHostile(temp->GetText() == "1" ? true : false);
	}

	temp = element->FirstChildElement("Talk");
	if (temp != nullptr) {
		c->setTalk(temp->GetText() == nullptr ? "" : temp->GetText());
	}

	return c;
}

XMLElement* CharacterDao::CharacterToXml(Character* c) {
	XMLElement* root = xml->createElement("Character");

	if (c->getId() != -1) {
		root->SetAttribute("id", c->getId());
	}

	const int ATTRIBUTE_COUNT = 14;
	string attributes[ATTRIBUTE_COUNT][2] = {
		{ "Class",			classToString(c->getCharacterClass()) },
		{ "Name",			c->getName() },
		{ "Level",			to_string(c->getLevel()) },
		{ "MaxHP",			to_string(c->getMaxHP()) },
		{ "CurrentHP",		to_string(c->getHP()) },
		{ "Strength",		to_string(c->getStat(Character::Stats::STR)) },
		{ "Constitution",	to_string(c->getStat(Character::Stats::CON)) },
		{ "Dexterity",		to_string(c->getStat(Character::Stats::DEX)) },
		{ "Intelligence",	to_string(c->getStat(Character::Stats::INT)) },
		{ "Wisdom",			to_string(c->getStat(Character::Stats::WIS)) },
		{ "Charisma",		to_string(c->getStat(Character::Stats::CHA)) },
		{ "EquipmentID",	to_string(c->getEquipID()) },
		{ "Hostile",		c->isHostile() ? "1" : "0" },
		{ "Talk",			c->getTalk() }
	};

	for (int i = 0; i < ATTRIBUTE_COUNT; i++) {
		XMLElement* classEle = xml->createElement(attributes[i][0]);
		classEle->SetText(attributes[i][1].c_str());
		root->InsertEndChild(classEle);
	}

	return root;
}


string CharacterDao::classToString(Character::Class c) {
	switch (c) {
		case Character::Class::FIGHTER:
			return "fighter";
			break;
		case Character::Class::ARCHER:
			return "archer";
			break;
		default: 
			return "Error: undefined Class" + c;
			break;
	}
}

Character::Class CharacterDao::stringToClass(string c) {
	if (c == "fighter") {
		return Character::Class::FIGHTER;
	}
	else if (c == "archer") {
		return Character::Class::ARCHER;
	}
	else {
		return Character::Class::BLABLA;
	}
}