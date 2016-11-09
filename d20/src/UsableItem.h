#pragma once
#include "Item.h"

class UsableItem : public Item {
public:
	UsableItem(Usable, string name = "Unknown Usable Item", ItemStats s = NUL, int bonus = 0);
	virtual string getCategoryStr();
	virtual void setStat(ItemStats);
	Usable getType();
	virtual string getTypeStr();
protected:
	Usable useType;
};