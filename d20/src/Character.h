//! @file 
//! @brief Header file for the Character class
//!

#pragma once
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <string>
#include "Die.h"

#define NUM_STATS 6
#define NUM_EQUIPMENT 6

const enum Stats {
	STR = 0, CON, DEX, INT, WIS, CHA
};

const enum Equipment {
	ARMOR = 0, SHIELD, WEAPON, BOOTS, RING, HELMET
};

using namespace std;

//! Character class
class Character {

public:
	int hit(int);
	int getStat(Stats stat) const;
	int getModifier(Stats stat) const;
	int getLevel() const;
	string getName() const;
	string getCharacterClass() const;
	int getArmor() const;
	int getHP() const;
	int getMaxHP() const;
	int getInvID() const;
	int getEquipID() const;
	virtual int getAtkBonus() const = 0;
	virtual int getDmgBonus() const = 0;
	int statChooser() const;
	bool validateNewCharacter();
	void printStats() const;
	Die die;
	
private:
	virtual void levelUp() = 0;
	int calcModifier(int) const;
	

protected:
	string charName;
	string charClass;
	int equipment[NUM_EQUIPMENT];
	int abilityScores[NUM_STATS];
	int lvl;
	int maxHP;
	int currentHP;
	int equipID;
	int invID;
	
	Character(string charClass, string charName, int equipID, int invID);
	~Character();
	vector<int> rollAbilityScores() const;
	int rollHP() const;
};