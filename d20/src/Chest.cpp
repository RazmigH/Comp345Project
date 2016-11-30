#include "Chest.h"
#include "ChestEditPane.h"

const string Chest::IDENTIFIER = "Chest";

Chest::Chest(ChestState state) : Tile("chests", true), state(state) {
	setId("chest");
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

	/*
	XMLElement* entry = xml->createElement("Start");
	entry->SetText(isEntryTile() ? "1" : "0");
	parent->InsertEndChild(entry);

	XMLElement* finish = xml->createElement("Finish");
	finish->SetText(isFinishTile() ? "1" : "0");
	parent->InsertEndChild(finish);
	*/

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