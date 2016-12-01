#include "EquipableItem.h"
#include <iostream>

EquipableItem::EquipableItem(Equipable type, string name, ItemStats s, int bonus) :
	equipType(type), Item(name, s, bonus) {
	string imagename = getTypeStr();
	setImage(imagename);
}

EquipableItem* EquipableItem::createEquipableItem() {
	string n = "";
	Equipable t = RING;
	ItemStats s = NUL;
	int b = 0, option;

	cout << "Please fill the form to create an equipable item" << endl;
	cout << "Choose an option for item type: 1->Helmet 2->Armor 3->Shield 4->Ring" << endl;
	cout << "5->Belt 6->Boots 7->Weapon" << endl;
	cout << "Your choice: ";
	cin >> option;
	switch (option) {
	case 1: t = HELMET;
	case 2: t = ARMOR;
	case 3: t = SHIELD;
	case 4: t = RING;
	case 5: t = BELT;
	case 6: t = BOOTS;
	case 7: t = WEAPON;
	}
	cout << "Enter the name of the item: ";
	cin >> n;
	
	cout << "Choose an option for the stat 1->Strength 2->Condition 3->Dexterity " << endl;
	cout << "4->Intelligenc 5->Wisdom 6->Charisma 7->Attack Bonus 8->Damage Bonus" << endl;
	cout << "9->Armor Class 10->None" << endl;
	cout << "Your choice: ";
	cin >> option;

	switch (option) {
	case 1: s = STR;
	case 2: s = CON;
	case 3: s = DEX;
	case 4: s = INT;
	case 5: s = WIS;
	case 6: s = CHA;
	case 7: s = ATK;
	case 8: s = DMG;
	case 9: s = ARM;
	case 10: s = NUL;
	}

	cout << "Enter the bonus amount: ";
	cin >> b;

	return new EquipableItem(t, n, s, b);
}

string EquipableItem::getCategoryStr() {
	return "equipable_item";
}

Item::Equipable EquipableItem::getType() {
	return equipType;
}

string EquipableItem::getTypeStr() {
	switch (equipType) {
	case HELMET: return "helmet"; break;
	case ARMOR: return "armor"; break;
	case SHIELD: return "shield"; break;
	case RING: return "ring"; break;
	case BELT: return "belt"; break;
	case BOOTS: return "boots"; break;
	case WEAPON: return "weapon"; break;
	}
}

void EquipableItem::setType(Equipable itemType)
{
	Item::Equipable equipType(itemType);
}

void EquipableItem::setStat(ItemStats val) {
	stat = val;
	/* WHAT
	if (equipType == HELMET) {
		switch (val) {
		case INT: stat = INT; break;
		case WIS: stat = WIS; break;
		case ARM: stat = ARM; break;
		}
	}
	else if (equipType == ARMOR || equipType == SHIELD) {
		switch (val) {
		case ARM: stat = ARM; break;
		} 
	}
	else if (equipType == RING) {
		switch (val) {
		case STR: stat = STR; break;
		case CON: stat = CON; break;
		case WIS: stat = WIS; break;
		case CHA: stat = CHA; break;
		}
	}
	else if (equipType == BELT) {
		switch (val) {
		case STR: stat = STR; break;
		case CON: stat = CON; break;
		}
	}
	else if (equipType == BOOTS) {
		switch (val) {
		case DEX: stat = DEX; break;
		case ARM: stat = ARM; break;
		}
	}
	else if (equipType == WEAPON) {
		switch (val) {
		case ATK: stat = ATK; break;
		case DMG: stat = DMG; break;
		}
	}
	else {
		switch (val) {
		case STR: stat = STR; break;
		case CON: stat = CON; break;
		case DEX: stat = DEX; break;
		case INT: stat = INT; break;
		case WIS: stat = WIS; break;
		case CHA: stat = CHA; break;
		case ATK: stat = ATK; break;
		case DMG: stat = DMG; break;
		case ARM: stat = ARM; break;
		}
	}*/
}


EquipableItem::EquipableItem() {
	equipType = EquipableItem::Equipable::HELMET;
	setStat(ItemStats::WIS);
}
EquipableItem::~EquipableItem() {}