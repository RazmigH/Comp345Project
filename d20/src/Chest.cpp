#include "Chest.h"
#include "ChestEditPane.h"
#include "EquipableItem.h"
#include "ChestDisplay.h"

const string Chest::IDENTIFIER = "Chest";

Chest::Chest(ChestState state) : Tile("chests", true), state(state) {
	setState(state);

	spEquipableItem item1 = new EquipableItem(Item::Equipable::WEAPON);
	item1->setStat(Item::ItemStats::STR);
	item1->setBonus(13);
	items.push_back(item1);
	spEquipableItem item2 = new EquipableItem(Item::Equipable::ARMOR);
	item2->setStat(Item::ItemStats::CON);
	item2->setBonus(7);
	items.push_back(item2);
}

Chest::~Chest() {

}

Chest::ChestState Chest::getState() {
	return state;
}

void Chest::setState(ChestState state) {
	this->setColumn(state == ChestState::CLOSED ? 1 : 0);
	this->setRow(0);
}

tinyxml2::XMLElement* Chest::getXML(Xml* xml) {
	XMLElement* parent = xml->createElement(IDENTIFIER);

	XMLElement* stateXml = xml->createElement("State");
	stateXml->SetText(state == ChestState::OPEN ? "open" : "closed");
	parent->InsertEndChild(stateXml);

	return parent;
}

spTile Chest::getFromXML(XMLElement* element) {
	spChest chest = new Chest();
	XMLElement* stateXml = element->FirstChildElement("State");
	if (stateXml != nullptr) {
		chest->setState(stateXml->GetText() == "open" ? ChestState::OPEN : ChestState::CLOSED);
	}
	return chest;
}

string Chest::getIdentifier() {
	return IDENTIFIER;
}

void Chest::addItem(spItem item) {
	items.push_back(item);
}

void Chest::removeItem(spItem item) {
	for (vector<spItem>::iterator it = items.begin(); it != items.end(); ++it) {
		if (item->getObjectID() == (*it)->getObjectID()) {
			items.erase(it);
			break;
		}
	}
}

void Chest::interact() {
	log::messageln("CHEST interact");
	spChestDisplay display = new ChestDisplay(this);
	
	flow::show(display, [=](Event*) {
		vector<spItem> selected = display->getItems();

		for (vector<spItem>::iterator it = selected.begin(); it != selected.end(); ++it) {
			character->addToInventory(*it);
			removeItem(*it);
		}
	});
}

vector<spItem> Chest::getItems() {
	return items;
}

void Chest::setCharacter(spCharacter c) {
	character = c;
}