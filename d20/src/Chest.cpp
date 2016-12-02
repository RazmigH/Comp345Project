#include "Chest.h"
#include "ChestEditPane.h"
#include "EquipableItem.h"
#include "ChestDisplay.h"

const string Chest::IDENTIFIER = "Chest";

Chest::Chest(ChestState state) : Tile("chests", true), state(state) {
	setState(state);

	const int r1 = (rand() % 100) + 1;
	for (int i = 0; i < r1; i++) {
		int r2 = (rand() % 7);
		Item::Equipable type = static_cast<Item::Equipable>(r2);

		int r3 = (rand() % 11);
		Item::ItemStats stat = static_cast<Item::ItemStats>(r3);

		int bonus = (rand() % 15) + 1;

		spEquipableItem item = new EquipableItem(type);
		item->setStat(stat);
		item->setBonus(bonus);

		items.push_back(item);
	}
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