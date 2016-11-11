#include "itemDao.h"
using namespace std;

ItemDao::ItemDao() {
	xml = new Xml("Items");
}

ItemDao::~ItemDao() {
	//xml = nullptr;
	delete(xml);
}

vector<spItem> ItemDao::getItems() {
	vector<spItem> items;
	vector<XMLElement*> elements = xml->getElements();
	for (std::vector<XMLElement*>::iterator it = elements.begin(); it != elements.end(); ++it) {
		spItem temp = XmlToItem(*it);
		items.push_back(temp);
	}
	return items;
}

spItem ItemDao::getItem(string id) {
	XMLElement* ele = xml->getElement(id);
	if (ele != nullptr) {
		return XmlToItem(ele);
	}
	return nullptr;
}

int ItemDao::addItem(spItem c) {
	return xml->addElement(ItemToXml(c));
}

spItem ItemDao::XmlToItem(XMLElement* element) {
	spItem c = new EquipableItem();

	const char* idstr = element->Attribute("id");
	if (idstr != nullptr) {
		c->setId(atoi(idstr));
	}

	int i;

	XMLElement* temp = element->FirstChildElement("Type");
	if (temp != nullptr) {
		//c->setType(stringToEquipable(temp->GetText()));
	}

	temp = element->FirstChildElement("Name");
	if (temp != nullptr) {
		c->setName(temp->GetText() == nullptr ? "Good luck!" : temp->GetText());
	}

	temp = element->FirstChildElement("Item Stat");
	if (temp != nullptr) {

		c->setStat(stringToItemStats(temp->GetText()));
	}

	temp = element->FirstChildElement("Bonus");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setBonus(i);
	}

	return c;
}

XMLElement* ItemDao::ItemToXml(spItem c) {
	XMLElement* root = xml->createElement("Equipable Item");

	if (c->getId() != -1) {
		root->SetAttribute("id", c->getId());
	}

	const int ATTRIBUTE_COUNT = 4;
	string attributes[ATTRIBUTE_COUNT][2] = {
		//{ "Type",			typeToString(c->getType()) },
		{ "Name",			c->getName() },
		{ "Item Stat",		to_string(c->getStat()) },
		{ "Bonus",			to_string(c->getBonus()) },

	};

	for (int i = 0; i < ATTRIBUTE_COUNT; i++) {
		XMLElement* classEle = xml->createElement(attributes[i][0]);
		classEle->SetText(attributes[i][1].c_str());
		root->InsertEndChild(classEle);
	}

	return root;
}


string ItemDao::typeToString(EquipableItem::Equipable c) {
	switch (c) {
	case EquipableItem::Equipable::HELMET: return "helmet"; break;
	case EquipableItem::Equipable::ARMOR: return "armor"; break;
	case EquipableItem::Equipable::SHIELD: return "shield"; break;
	case EquipableItem::Equipable::RING: return "ring"; break;
	case EquipableItem::Equipable::BELT: return "belt"; break;
	case EquipableItem::Equipable::BOOTS: return "boots"; break;
	case EquipableItem::Equipable::WEAPON: return "weapon"; break;
	default:return "Error: undefined type" + c; break;
	}
}

EquipableItem::Equipable ItemDao::stringToEquipable(string c) {
	if (c == "helmet") { return EquipableItem::Equipable::HELMET; }
	else if (c == "armor") { return EquipableItem::Equipable::ARMOR; }
	else if (c == "shield") { return EquipableItem::Equipable::SHIELD; }
	else if (c == "ring") { return EquipableItem::Equipable::RING; }
	else if (c == "belt") { return EquipableItem::Equipable::BELT; }
	else if (c == "boots") { return EquipableItem::Equipable::BOOTS; }
	else { return EquipableItem::Equipable::WEAPON; }
}

EquipableItem::ItemStats ItemDao::stringToItemStats(string c) {
	if (c == "STR") { return EquipableItem::ItemStats::STR; }
	else if (c == "CON") { return EquipableItem::ItemStats::CON; }
	else if (c == "DEX") { return EquipableItem::ItemStats::DEX; }
	else if (c == "INT") { return EquipableItem::ItemStats::INT; }
	else if (c == "WIS") { return EquipableItem::ItemStats::WIS; }
	else if (c == "CHA") { return EquipableItem::ItemStats::CHA; }
	else if (c == "ATK") { return EquipableItem::ItemStats::ATK; }
	else if (c == "DMG") { return EquipableItem::ItemStats::DMG; }
	else if (c == "ARM") { return EquipableItem::ItemStats::ARM; }
	else if (c == "CHP") { return EquipableItem::ItemStats::CHP; }
	else { return EquipableItem::ItemStats::NUL; }
}