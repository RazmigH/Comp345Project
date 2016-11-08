#pragma once
#include "Character.h"
#include "Xml.h"

using namespace std;

class CharacterDao{
public:
	CharacterDao();
	~CharacterDao();
	vector<Character*> getCharacters();
	int addCharacter(Character* c);
private: 
	Xml* xml;
	Character* XmlToCharacter(XMLElement*);
	XMLElement* CharacterToXml(Character*);

	string classToString(Character::Class);
	Character::Class stringToClass(string);
};