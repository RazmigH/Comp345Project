//! @file 
//! @brief Implementation file for the Fighter class  
//!

#pragma once
#include "Fighter.h"

Fighter::Fighter(string characterName) : Character("Fighter", characterName){
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
	currentHitPoints = maxHP;
}

Fighter::Fighter(string characterName, int level): Fighter(characterName) {
	for (int i = lvl; i < level; ++i) {
		levelUp();
	}
}

Fighter::Fighter(string charName, int lvl, int strength, int constitution, int dexterity, 
	int intelligence, int wisdom, int charisma) : Fighter(charName, lvl){
	abilityScores[STR] = strength;
	abilityScores[CON] = constitution;
	abilityScores[DEX] = dexterity;
	abilityScores[INT] = intelligence;
	abilityScores[WIS] = wisdom;
	abilityScores[CHA] = charisma;
	maxHP = 10 + getModifier(CON); //! first lvl hp always 10 + constitution modifier
	currentHitPoints = maxHP;
}

//! Fighter::levelUP() -> increases the level, increases the hp, assigns an ability point
//! every 4 levels (alternates between strength-condition)
void Fighter::levelUp() {
	++lvl;
	cout << "Level up! Level " << lvl << " reached!" << endl;
	maxHP += roll10() + getModifier(CON);
	currentHitPoints = maxHP;

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

