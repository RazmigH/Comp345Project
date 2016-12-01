#pragma once

#include "oxygine-framework.h"
#include "Xml.h"
#include <string>
using namespace oxygine;

DECLARE_SMART(Tile, spTile);
class Tile : public Sprite {
public:
	static const int BASE_SPRITE_SIZE = 32;
	static const string IDENTIFIER;

	Tile(std::string = "transparent", bool solid = false, int col = 0, int row = 0);
	Tile(const spTile);
	~Tile();

	void setImage(std::string, int col = 0, int row = 0);
	void setImage(const ResAnim*, int col = 0, int row = 0);
	string getImageName() const;
	bool isSolid();
	void isSolid(bool);

	virtual spTile clone() {
		spTile tile = new Tile(this->getResAnim()->getName(), this->solid, this->getColumn(), this->getRow());
		return tile;
	}
	virtual tinyxml2::XMLElement* getXML(Xml*); //! return an XML representation of the tile.
	static spTile getFromXML(XMLElement*); //! get Tile with properties provided in XML.

	bool operator==(const Tile&) const;
	bool operator!=(const Tile&) const;
	void Tile::doRender(const RenderState& rs);
	virtual string getIdentifier();

	virtual void interact() {}
private:
	bool solid;
};
