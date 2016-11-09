#include "UsableItem.h"

UsableItem::UsableItem(Usable type, string name, ItemStats s, int bonus) :
	useType(type), Item(name, s, bonus){

}

string UsableItem::getCategoryStr() {
	return "usable_item";
}

Item::Usable UsableItem::getType() {
	return useType;
}

string UsableItem::getTypeStr() {
	switch(useType) {
	case KEY: return "key"; break;
	case POTION: return "potion"; break;
	}
}
void UsableItem::setStat(ItemStats val) {
	if (useType == POTION) {
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
		case CHP: stat = CHP; break;
		}
	}
}
