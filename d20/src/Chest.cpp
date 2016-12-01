#include "Chest.h"
#include "ChestEditPane.h"

const string Chest::IDENTIFIER = "Chest";

Chest::Chest(ChestState state) : Tile("chests", true), state(state) {
	setState(state);
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

void Chest::interact() {
	log::messageln("CHEST interact");
}