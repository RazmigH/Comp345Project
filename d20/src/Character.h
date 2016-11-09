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
#include "Tile.h"

#define NUM_STATS 6
#define NUM_EQUIPMENT 6

using namespace std;

//! Character class
DECLARE_SMART(Character, spCharacter);
class Character : public Tile{

public:
	const enum Stats {
		STR = 0, CON, DEX, INT, WIS, CHA
	};

	const enum Class {
		FIGHTER = 0, ARCHER, BLABLA
	};

	//put into items when ready
	const enum Equipment {
		ARMOR = 0, SHIELD, WEAPON, BOOTS, RING, HELMET
	};

	Character(
		Class = FIGHTER, 
		string name = "Generic Character", 
		int level = 1, 
		int equipmentID = 0,
		int invID = 0,
		bool hostile = false, 
		string strTalk = "Good luck!",
		bool player = false
	);

	~Character(); 
	
	virtual int takeDmg(int);

	//id
	int getId() const;
	void setId(int);

	//Stats
	int getStat(Stats stat) const;
	void setStat(Stats stat, int value);

	int getModifier(Stats stat) const;
	int getLevel() const;
	void setLevel(int);

	//Character Class
	Class getCharacterClass() const;
	void setCharacterClass(Class);

	int getArmor() const;


	//Hitpoints
	int getHP() const;
	void setHP(int);

	//Max hitpoints
	int getMaxHP() const;
	void setMaxHP(int);

	//Inventory
	int getInvID() const;
	void setInvID(int);

	//Equipment
	int getEquipID() const;
	void setEquipID(int);

	//Character Name
	string getName() const;
	void setName(string);

	string getNameCharacterClass() const;

	int getAtkBonus() const;
	int getDmgBonus() const;
	int statChooser() const;
	bool validateNewCharacter();
	virtual void printStats() const;
	bool isDead() const;
	Die die;

	string getTalk() const;
	void setTalk(string);

	//hostile
	bool isHostile() const; 
	void setHostile(bool);

	//armor
	int getArmorVar() const;
	void setArmorVar(int);

	//atkBonus
	int getAtkBonusVar() const;
	void setAtkBonusVar(int);

	//dmgBonus
	int getDmgBonusVar() const;
	void setDmgBonusVar(int);
	bool isPlayer() const;

	int inflictDamage(Character &);
	
	//anims
	void setUp();
	void setDown();
	void setLeft();
	void setRight();
private:
	virtual void levelUp();
	int calcModifier(int) const;
	
protected:
	int id;
	Class charClass;

	int equipment[NUM_EQUIPMENT];
	int abilityScores[NUM_STATS];
	int lvl;
	int maxHP;
	int armor;
	int atkBonus;
	int dmgBonus;
	int currentHP;
	int equipID;
	int invID;
	bool dead;
	string charName;
	string strTalk;
	bool player;
	bool hostile;
	
	vector<int> rollAbilityScores() const;
	int rollHP() const;
	void endGame();

};