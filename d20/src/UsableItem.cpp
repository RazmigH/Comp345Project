#include "UsableItem.h"
#include <iostream>

UsableItem::UsableItem(Usable type, string name, ItemStats s, int bonus) :
	useType(type), Item(name, s, bonus){

}

UsableItem* UsableItem::createUsableItem() {
	string n = "";
	Usable t = POTION;
	ItemStats s = NUL;
	int b = 0, option;

	cout << "Please fill the form to create an usable item" << endl;
	cout << "Choose an option for item type: 1->Key 2->Potion" << endl;
	cout << "Your choice: ";
	cin >> option;
	switch (option) {
	case 1: t = KEY;
	case 2: t = POTION;
	}
	cout << "Enter the name of the item: ";
	cin >> n;

	cout << "Choose an option for the stat 1->Strength 2->Condition 3->Dexterity " << endl;
	cout << "4->Intelligenc 5->Wisdom 6->Charisma 7->Attack Bonus 8->Damage Bonus" << endl;
	cout << "9->Armor Class 10->Current Hit Points 11->None" << endl;
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
	case 10: s = CHP;
	case 11: s = NUL;
	}

	cout << "Enter the bonus amount: ";
	cin >> b;

	return new UsableItem(t, n, s, b);
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
