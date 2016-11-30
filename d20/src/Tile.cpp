#include "Tile.h"
#include "GameResource.h"
#include "DefaultEditPane.h"
#include "Chest.h"

const string Tile::IDENTIFIER = "Tile";

Tile::Tile(std::string image, bool solid, int img_row, int img_col) : solid(solid) {
	setSize(BASE_SPRITE_SIZE, BASE_SPRITE_SIZE);
	setImage(image, img_row, img_col);
	setName(image);
	id = "tile";
}

Tile::Tile(const spTile tile) : solid(tile->solid), id(tile->getId()) {
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

bool Tile::operator==(const Tile& other) const {
	return this->getResAnim() == other.getResAnim() &&
		this->getColumn() == other.getColumn() &&
		this->getRow() == other.getRow();
}

bool Tile::operator!=(const Tile& other) const {
	return !(*this == other);
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

	return tile;
}

string Tile::getImageName() const{
	return getResAnim()->getName();
}

void Tile::doRender(const RenderState& rs) {
	Sprite::doRender(rs);
	float wratio = getWidth() / BASE_SPRITE_SIZE;
	float hratio = getHeight() / BASE_SPRITE_SIZE;
	setScale(wratio, hratio);
}

string Tile::getId() {
	return id;
}
void Tile::setId(string id) {
	this->id = id;
}