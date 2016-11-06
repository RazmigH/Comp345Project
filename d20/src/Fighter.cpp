//! @file 
//! @brief Implementation file for the Fighter class  
//!

#pragma once
#include "Fighter.h"

Fighter::Fighter(string characterName, int equipmentID, int inventoryID) : 
	Character("Fighter", characterName, equipmentID, inventoryID){
	vector<int> scores;
	scores = rollAbilityScores();
	//! sort from low to high in order to decide the assigment priority
	sort(scores.begin(), scores.end());
	//! ability scores are assigned depending on the priority for the
	//! character's class: first one is the lowest
	abilityScores[INT] = scores.at(0);
	abilityScores[CHA] = scores.at(1);
	abilityScores[WIS] = scores.at(2);
	abilityScores[DEX] = scores.at(3);
	abilityScores[CON] = scores.at(4);
	abilityScores[STR] = scores.at(5);
	maxHP = 10 + getModifier(CON); //! first lvl hp always 10 + constitution modifier
	currentHP = maxHP;
}

Fighter::Fighter(string characterName, int level, int equipmentID, int inventoryID) : 
	Fighter(characterName, equipmentID, inventoryID) {
	for (int i = lvl; i < level; ++i) {
		levelUp();
	}
}

Fighter::Fighter(
	string charName, 
	int lvl, 
	int maxHP, 
	int currHP,
	int strength, 
	int constitution, 
	int dexterity,
	int intelligence, 
	int wisdom, 
	int charisma,
	int equipmentID, 
	int inventoryID) : Character("Fighter", charName, equipmentID, inventoryID)
{
	this->lvl = lvl;
	abilityScores[STR] = strength;
	abilityScores[CON] = constitution;
	abilityScores[DEX] = dexterity;
	abilityScores[INT] = intelligence;
	abilityScores[WIS] = wisdom;
	abilityScores[CHA] = charisma;
	this->maxHP = maxHP;
	currentHP = currHP;

}

//! Fighter::levelUP() -> increases the level, increases the hp, assigns an ability point
//! every 4 levels (alternates between strength-condition)
void Fighter::levelUp() {
	++lvl;
	cout << "Level up! Level " << lvl << " reached!" << endl;
	maxHP += roll10() + getModifier(CON);
	currentHP = maxHP;

	if (lvl % 4 == 0) {
		if (lvl % 8 == 0) {
			abilityScores[CON] += 1;
		}
		else {
			abilityScores[STR] += 1;
		}
	}
	/*
	if (lvl % 4 == 0) {
		cout << "New ability point awarded! Where do you want to asign it?" << endl;
		int choice = statChooser();
		abilityScores[choice] += 1;
	}
	*/
}

int Fighter::getAtkBonus() const {
	return roll20() + getModifier(STR);
}

int Fighter::getDmgBonus() const {
	return roll6() + getModifier(STR);
}

