//! @file 
//! @brief Implementation file for the Character class  
//!

#include "Character.h"

Character::Character(Class characterClass, string characterName, int equipmentID, int inventoryID) 
	: charClass(characterClass), equipID(equipmentID), invID(inventoryID){
	setName(characterName);
	lvl = 1;
	dead = false;
	id = -1;
}

Character::~Character() {
}

vector<int> Character::rollAbilityScores() const {
	vector<int> scores = {};
	for (int i = 0; i < NUM_STATS; ++i) {
		vector<int> rolls;
		for (int j = 0; j < 4; ++j) {
			rolls.push_back(die.roll6());
		}
		sort(rolls.begin(), rolls.end()); //! sort ascending order
		int stat = 0;
		//! skip the first roll, because he's the smallest one after the sort
		for (int i = 1; i < 4; ++i) {
			stat += rolls.at(i);
		}
		scores.push_back(stat);
	}
	
	cout << "Character stats roll result: ";
	for (int i = 0; i < scores.size(); ++i) {
		cout << scores.at(i) << " ";
	}
	cout << endl;

	return scores;
}

int Character::rollHP() const {
	return die.roll10();
}

int Character::calcModifier(int num) const {
	//! lowest modifier for any number below 0
	if (num <= 0) {
		return -5;
	}
	//! negative modifiers below 10
	else if (num < 10) {
		return (num - 11) / 2;
	}
	else {
		return (num - 10) / 2;
	}
}

int Character::takeDmg(int dmg) {
	currentHP -= dmg;
	//! calls notify every time the character gets hit
	if (currentHP <= 0) {
		dead = true;
		cout << "You DIED!";
		endGame();
	}
	return currentHP;
}

void Character::endGame() {

}

int Character::getId() const{
	return id;
}
void Character::setId(int id) {
	this->id = id;
}

int Character::getLevel() const {
	return lvl;
}

void Character::setLevel(int level) {
	lvl = level;
}

int Character::getInvID() const {
	return invID;
}

void Character::setInvID(int id) {
	invID = id;
}

int Character::getEquipID() const {
	return equipID;
}

void Character::setEquipID(int id) {
	equipID = id;
}

int Character::getStat(Stats stat) const {
	return abilityScores[stat];
}

void Character::setStat(Stats stat, int value) {
	abilityScores[stat] = value;
}

int Character::getModifier(Stats stat) const {
	return calcModifier(abilityScores[stat]);
}

Character::Class Character::getCharacterClass() const {
	return charClass;
}

void Character::setCharacterClass(Class c)
{
	this->charClass = c;
}

int Character::getArmor() const {
	return 10 + getModifier(DEX);
}

int Character::getHP() const {
	return currentHP;
}

void Character::setHP(int hp) {
	this->currentHP = hp;
}

int Character::getMaxHP() const {
	return maxHP;
}

void Character::setMaxHP(int hp) {
	maxHP = hp;
}

bool Character::isDead() const {
	return (dead == true) ? true : false;
}

//! TODO: prob will not be used for the project
int Character::statChooser() const {
	cout << "Please choose the stat: " << endl;
	cout << "Strength -> 1" << endl;
	cout << "Condition -> 2" << endl;
	cout << "Dexterity -> 3" << endl;
	cout << "Intelligence -> 4" << endl;
	cout << "Wisdom -> 5" << endl;
	cout << "Charisma -> 6" << endl;
	cout << "Input the number corresponding to your choice: ";
	int choice = 1;
	cin >> choice;
	switch (choice) {
	case 1: return STR; break;
	case 2: return CON; break;
	case 3: return DEX; break;
	case 4: return INT; break;
	case 5: return WIS; break;
	case 6: return CHA; break;
	default: cout << "Invalid choice! Try again..." << endl;
	return statChooser();
	}
}
bool Character::validateNewCharacter() {
	for (int i = 0; i < NUM_STATS; ++i) {
		if (abilityScores[i] < (3 + lvl/4) || abilityScores[i] > (18 + lvl/4)) {
			return false;
		}
	}
	return true;
}

void Character::printStats() const {
	cout << "****Character Info****" << endl;
	cout << "Id: " << getId() << endl;
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
}


int Character::getAtkBonus() const {
	return die.roll20() + getModifier(STR);
}

int Character::getDmgBonus() const {
	return die.roll6() + getModifier(STR);
}

//! Character::levelUP() -> increases the level, increases the hp, assigns an ability point
//! every 4 levels (alternates between strength-condition)
void Character::levelUp() {
	++lvl;
	cout << "Level up! Level " << lvl << " reached!" << endl;
	maxHP += die.roll10() + getModifier(CON);
	currentHP = maxHP;

	if (lvl % 4 == 0) {
		if (lvl % 8 == 0) {
			abilityScores[CON] += 1;
		}
		else {
			abilityScores[STR] += 1;
		}
	}
}


bool Character::isHostile() const {
	return hostile;
}

void Character::isHostile(bool h) {
	hostile = h;
}

string Character::getTalk() const {
	return strTalk;
}

void Character::setTalk(string t) {
	strTalk = t;
}

int Character::inflictDamage(int dmg) {
	if (!isHostile()) {
		cout << "Cannot attack a non-hostile enemy!";
		return currentHP;
	}

	currentHP -= dmg;
	if (currentHP <= 0) {
		dead = true;
		cout << getName() + " was killed!";
		//getItems();
		//removeFromMap();
	}
	return currentHP;
}