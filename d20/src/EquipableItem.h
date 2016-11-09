#pragma once
#include "Item.h"

class EquipableItem : public Item{
public:
public:
	EquipableItem(Equipable, string name = "Unknown Equipable Item", ItemStats s = NUL, int bonus = 0);
	virtual string getCategoryStr();
	Equipable getType();
	virtual string getTypeStr();
	virtual void setStat(ItemStats);
protected:
	Equipable equipType;

};