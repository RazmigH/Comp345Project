#pragma once
#include "Character.h"
#include "Xml.h"

using namespace std;

class CharacterDao{
public:
	CharacterDao();
	~CharacterDao();
	vector<spCharacter> getCharacters();
	spCharacter getCharacter(string id);
	int addCharacter(spCharacter c);
private: 
	Xml* xml;
};