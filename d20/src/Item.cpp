#include "Item.h"
#include <iostream>

Item::Item(string n, ItemStats s, int b) :
	stat(s),
	bonus(b)
{
	setName(n);
	id = -1;
}

void Item::printDetails() {
	log::messageln("******Item Info******");
	log::messageln("Name: %s", getName());
	log::messageln("Category: %s", getCategoryStr());
	log::messageln("Type: %s", getTypeStr());
	log::messageln("Stat: %s", getStatStr());
	log::messageln("Bonus Value: %d", getBonus());
}

string Item::getStatStr() const {
	switch (stat) {
	case STR: return "strength"; break;
	case CON: return "condition"; break;
	case DEX: return "dexterity"; break;
	case INT: return "intelligence"; break;
	case WIS: return "wisdom"; break;
	case CHA: return "charisma"; break;
	case ATK: return "atk_bonus"; break;
	case DMG: return "dmg_bonus"; break;
	case ARM: return "armor_bonus"; break;
	case CHP: return "current_hp"; break;
	case NUL: return "none"; break;
	}
}

Item::ItemStats Item::getStat() {
	return stat;
}

int Item::getBonus() const {
	return bonus;
}

void Item::setBonus(int val) {
	if (val < 0) {
		bonus = 0;
	}
	// potions for HP can have more than 5 for the bonus value
	else if (val > 5 && stat != CHP) {
		bonus += 5;
	}
	else {
		bonus += val;
	}
}

int Item::getId() {
	return id;
}

void Item::setId(int id) {
	this->id = id;
}

