#include "EquipableItem.h"

EquipableItem::EquipableItem(Equipable type, string name, ItemStats s, int bonus) :
	equipType(type), Item(name, s, bonus) {

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

void EquipableItem::setStat(ItemStats val) {
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
}