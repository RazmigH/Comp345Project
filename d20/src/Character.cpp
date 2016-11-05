//! @file 
//! @brief Implementation file for the Character class  
//!

#include "stdafx.h"
#include "Character.h"


Character::Character(string characterClass, string characterName){
	charClass = characterClass;
	charName = characterName;
	lvl = 1;
	srand(time(NULL)); //! seed for random generator based on time
}

Character::~Character() {
}


int Character::roll6() const {
	return (rand() % 6) + 1;
}

int Character::roll10() const {
	return (rand() % 10) + 1;
}

int Character::roll20() const {
	return (rand() % 20) + 1;
}

vector<int> Character::rollAbilityScores() const {
	vector<int> scores = {};
	for (int i = 0; i < NUM_STATS; ++i) {
		vector<int> rolls;
		for (int j = 0; j < 4; ++j) {
			rolls.push_back(roll6());
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
		cout << scores.at(i) << ", ";
	}

	return scores;
}

int Character::rollHP() const {
	return roll10();
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

int Character::hit(int dmg) {
	currentHitPoints -= dmg;
	//! calls notify every time the character gets hit
	if (currentHitPoints <= 0) {
		cout << "You DIED!";
	}
	return currentHitPoints;
}

int Character::getStat(Stats stat) const {
	switch (stat) {
	case STR: return abilityScores[STR]; break;
	case CON: return abilityScores[CON]; break;
	case DEX: return abilityScores[DEX]; break;
	case INT: return abilityScores[INT]; break;
	case WIS: return abilityScores[WIS]; break;
	case CHA: return abilityScores[CHA]; break;
	}
}

int Character::getModifier(Stats stat) const {
	switch (stat) {
	case STR: return calcModifier(abilityScores[STR]); break;
	case CON: return calcModifier(abilityScores[CON]); break;
	case DEX: return calcModifier(abilityScores[DEX]); break;
	case INT: return calcModifier(abilityScores[INT]); break;
	case WIS: return calcModifier(abilityScores[WIS]); break;
	case CHA: return calcModifier(abilityScores[CHA]); break;
	}
}

string Character::getCharacterClass() const {
	return charClass;
}

int Character::getArmor() const {
	return 10 + getModifier(DEX);
}

int Character::getHitPoints() const {
	return currentHitPoints;
}

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
	cout << "Name: " << charName << endl;
	cout << "Level: " << lvl << endl;
	cout << "Class: " << charClass << endl;
	cout << "Max HP: " << maxHP << endl;
	cout << "Current HP: " << currentHitPoints << endl;
	cout << "Strength: " << abilityScores[STR] << endl;
	cout << "Constitution: " << abilityScores[CON] << endl;
	cout << "Dexterity: " << abilityScores[DEX] << endl;
	cout << "Inteligence: " << abilityScores[INT] << endl;
	cout << "Wisdom: " << abilityScores[WIS] << endl;
	cout << "Charisma: " << abilityScores[CHA] << endl;

}