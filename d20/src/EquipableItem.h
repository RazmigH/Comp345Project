#pragma once
#include "Item.h"

class EquipableItem : public Item {
public:
public:
	EquipableItem(Equipable, string name = "Unknown Equipable Item", ItemStats s = NUL, int bonus = 0);
	EquipableItem();
	~EquipableItem();
	virtual string getCategoryStr();
	Equipable getType();
	virtual string getTypeStr();
	virtual void setStat(ItemStats);
	void setType(Equipable itemType);
protected:
	Equipable equipType;

};

typedef oxygine::intrusive_ptr<EquipableItem>spItem;