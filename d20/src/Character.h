//! @file 
//! @brief Header file for the Character class
//!

#pragma once
#include "stdafx.h"
#include <algorithm>
#include <time.h>

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
	string getCharacterClass() const;
	int getArmor() const;
	int getHitPoints() const;
	virtual int getAtkBonus() const = 0;
	virtual int getDmgBonus() const = 0;
	int statChooser() const;
	bool validateNewCharacter();
	void printStats() const;
	
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
	int currentHitPoints;
	
	Character(string charClass, string charName);
	~Character();
	vector<int> rollAbilityScores() const;
	int roll6() const;
	int roll10() const;
	int roll20() const;
	int rollHP() const;
};