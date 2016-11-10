#pragma once
#include "EquipableItem.h"
#include "UsableItem.h"
#include "Xml.h"

using namespace std;

class ItemDao {
public:
	ItemDao();
	~ItemDao();
	vector<spItem> getItems();
	spItem getItem(string);
	int addItem(spItem c);
private:
	Xml* xml;
	spItem XmlToItem(XMLElement*);
	XMLElement* ItemToXml(spItem);

	//string itemToString(Item::Class);
	UsableItem::Usable stringToUsable(string);
	EquipableItem::Equipable stringToEquipable(string);
	//Item::ItemStats stringToItemStats(string);
	EquipableItem::ItemStats stringToItemStats(string c);
	string typeToString(EquipableItem::Equipable);
};


