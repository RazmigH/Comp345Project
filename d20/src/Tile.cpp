#include <iostream>
#include "Tile.h"
#include "ImageResource.h"
#include "DefaultEditPane.h"
#include "Chest.h"

const string Tile::IDENTIFIER = "Tile";

Tile::Tile(std::string image, bool solid, int img_row, int img_col) : solid(solid) {
	setSize(TILE_SIZE, TILE_SIZE);
	setImage(image, img_row, img_col);
	setName(image);
}

Tile::Tile(const spTile tile) : solid(tile->solid) {
	setSize(tile->getSize());
	setImage(tile->getResAnim(), tile->getColumn(), tile->getRow());
	setName(tile->getName());
}

Tile::~Tile() {

}

void Tile::setImage(const ResAnim* resAnim, int col, int row) {
	setResAnim(resAnim, col, row);
}
void Tile::setImage(std::string imageName, int col, int row) {
	setImage(res::resources.getResAnim(imageName), col, row);
}

void Tile::isSolid(bool solid) {
	this->solid = solid;
}

bool Tile::isSolid() {
	return solid;
}

bool Tile::isEntryTile() {
	return isEntry;
}

bool Tile::isFinishTile() {
	return isFinish;
}

void Tile::isEntryTile(bool b) {
	isEntry = b;
}

void Tile::isFinishTile(bool b) {
	isFinish = b;
}

bool Tile::operator==(const Tile& other) const {
	return	this->getResAnim() == other.getResAnim() &&
		this->getColumn() == other.getColumn() &&
		this->getRow() == other.getRow();
}

bool Tile::operator!=(const Tile& other) const {
	return !(*this == other);
}

spActor Tile::getEditLayout() {
	spDefaultEditPane actor = new DefaultEditPane(this);
	return actor;
}

tinyxml2::XMLElement* Tile::getXML(Xml* xml) {
	XMLElement* parent = xml->createElement(IDENTIFIER);

	XMLElement* sprite = xml->createElement("Sprite");
	sprite->SetAttribute("row", this->getRow());
	sprite->SetAttribute("col", this->getColumn());
	sprite->SetText(this->getResAnim()->getName().c_str());
	parent->InsertEndChild(sprite);

	XMLElement* solid = xml->createElement("Solid");
	solid->SetText(isSolid() ? "1" : "0");
	parent->InsertEndChild(solid);

	XMLElement* entry = xml->createElement("Start");
	entry->SetText(isEntryTile() ? "1" : "0");
	parent->InsertEndChild(entry);

	XMLElement* finish = xml->createElement("Finish");
	finish->SetText(isFinishTile() ? "1" : "0");
	parent->InsertEndChild(finish);

	return parent;
}

spTile Tile::getFromXML(XMLElement* element) {
	if (element->Name() == Chest::IDENTIFIER) {
		return Chest::getFromXML(element);
	}

	spTile tile = new Tile();
	XMLElement* sprite = element->FirstChildElement("Sprite");
	if (sprite != nullptr) {
		int col = 0, row = 0;
		const char* colattr = sprite->Attribute("col");
		const char* rowattr = sprite->Attribute("row");;
		if (colattr != nullptr)
			col = stoi(colattr);
		if (rowattr != nullptr)
			row = stoi(rowattr);
		tile->setImage(sprite->GetText(), col, row);
	}

	XMLElement* solidXml = element->FirstChildElement("Solid");
	int solid;
	if (solidXml != nullptr && solidXml->QueryIntText(&solid) == XML_SUCCESS) {
		tile->isSolid(solid == 1 ? true : false);
	}

	XMLElement* startXml = element->FirstChildElement("Start");
	int start;
	if (startXml != nullptr && startXml->QueryIntText(&start) == XML_SUCCESS) {
		tile->isEntryTile(start == 1 ? true : false);
	}

	XMLElement* finishXml = element->FirstChildElement("Finish");
	int finish;
	if (finishXml != nullptr && finishXml->QueryIntText(&finish) == XML_SUCCESS) {
		tile->isFinishTile(finish == 1 ? true : false);
	}
	return tile;
}