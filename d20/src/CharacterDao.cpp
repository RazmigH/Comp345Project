#include "CharacterDao.h"
using namespace std;

CharacterDao::CharacterDao(){
	xml = new Xml("Characters");
}

CharacterDao::~CharacterDao() {
	//xml = nullptr;
	delete(xml);
}

vector<spCharacter> CharacterDao::getCharacters() {
	vector<spCharacter> chars;
	vector<XMLElement*> elements = xml->getElements();
	for(std::vector<XMLElement*>::iterator it = elements.begin(); it != elements.end(); ++it) {
		spCharacter temp = dynamic_cast<Character*>(&(*Character::getFromXML(*it)));
		chars.push_back(temp);
	}
	return chars;
}

spCharacter CharacterDao::getCharacter(string id) {
		XMLElement* ele = xml->getElement(id);
		if (ele != nullptr) {
			spCharacter temp = dynamic_cast<Character*>(&(*Character::getFromXML(ele)));
			return temp;
		}
		return nullptr;
}

int CharacterDao::addCharacter(spCharacter c) {
	return xml->addElement(c->getXML(xml));
}