#include "Npc.h"

Npc::Npc(string charName, int equipID, int invID) :
	Fighter(charName, equipID, invID) 
{
	hostile = false;
	strTalk = "Good luck!";
}

Npc::Npc(string charName, int lvl, int equipID, int invID) :
	Fighter(charName, lvl, equipID, invID)
{
	hostile = false;
	strTalk = "Good luck!";
}

Npc::Npc(string charName, int lvl, int maxHP, int currHP,
	int str, int con, int dex, int intl, int wis, int cha, int equipID, int invID) :
	Fighter(charName, lvl, maxHP, currHP, str, con, dex, intl, wis, cha, equipID, invID)
{
	hostile = false;
	strTalk = "Good luck!";
}

Npc::Npc(string charName, int equipID, int invID, bool hostile, string talk) :
	Fighter(charName, equipID, invID) 
{
	this->hostile = hostile;
	strTalk = talk;
}

Npc::Npc(string charName, int lvl, int equipID, int invID, bool hostile, string talk) :
	Fighter(charName, lvl, equipID, invID)
{
	this->hostile = hostile;
	strTalk = talk;
}

Npc::Npc(string charName, int lvl, int maxHP, int currHP, int str, int con, int dex, 
	int intl, int wis, int cha, int equipID, int invID, bool hostile, string talk) :
	Fighter(charName, lvl, maxHP, currHP, str, con, dex, intl, wis, cha, equipID, invID)
{
	this->hostile = hostile;
	strTalk = talk;
}

bool Npc::isHostile() const {
	return (hostile == true) ? true : false;
}

string Npc::getTalk() const {
	return strTalk;
}

int Npc::takeDmg(int dmg) {
	if (!isHostile()) {
		cout << "Cannot attack a non-hostile enemy!";
		return currentHP;
	}
	
	currentHP -= dmg;
	if (currentHP <= 0) {
		dead = true;
		cout << charName + " was killed!";
		getItems();
		removeFromMap();
	}
	return currentHP;
}


void Npc::getItems() {

}

void Npc::removeFromMap() {

}

void Npc::printStats() const {
	cout << "****Character Info****" << endl;
	cout << "Name: " << getName() << endl;
	cout << "Level: " << getLevel() << endl;
	cout << "Class: " << getCharacterClass() << endl;
	cout << "Max HP: " << getMaxHP() << endl;
	cout << "Current HP: " << getHP() << endl;
	cout << "Strength: " << abilityScores[STR] << endl;
	cout << "Constitution: " << abilityScores[CON] << endl;
	cout << "Dexterity: " << abilityScores[DEX] << endl;
	cout << "Inteligence: " << abilityScores[INT] << endl;
	cout << "Wisdom: " << abilityScores[WIS] << endl;
	cout << "Charisma: " << abilityScores[CHA] << endl;
	cout << "Equipment ID: " << getEquipID() << endl;
	cout << "Inventory ID: " << getInvID() << endl;
	cout << "Hostile: " << isHostile() << endl;
	cout << "Talk: " << getTalk() << endl;
}