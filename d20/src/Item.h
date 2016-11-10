#pragma once
#include "Character.h"

class Item : public Tile {
public:

	const enum Usable { KEY = 0, POTION };
	const enum Equipable { HELMET = 0, ARMOR, SHIELD, RING, BELT, BOOTS, WEAPON };
	const enum ItemStats { STR = 0, CON, DEX, INT, WIS, CHA, ATK, DMG, ARM, CHP, NUL };

	Item(string name = "Unknown Item", ItemStats s = NUL, int bonus = 0);

	void printDetails();


	virtual string getCategoryStr() = 0;
	virtual string getTypeStr() = 0;

	//stat
	string getStatStr() const;
	ItemStats getStat();
	virtual void setStat(ItemStats) = 0;

	//bonus
	int getBonus() const;
	void setBonus(int);


	int getId();
	void setId(int);

protected:
	int bonus;
	ItemStats stat;
	int id;
	string name;
};
//typedef oxygine::intrusive_ptr<Item>spItem;