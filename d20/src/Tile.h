#pragma once

#include "oxygine-framework.h"
#include "Xml.h"
using namespace oxygine;

DECLARE_SMART(Tile, spTile);
class Tile : public Sprite {
public:
	static const int TILE_SIZE = 32;

	Tile(std::string = "blank", bool solid = false, int col = 0, int row = 0);
	Tile(const spTile);
	~Tile();

	void setImage(std::string, int col = 0, int row = 0);
	void setImage(const ResAnim*, int col = 0, int row = 0);
	bool isSolid();
	void isSolid(bool);
	bool isEntryTile();
	void isEntryTile(bool);
	bool isFinishTile();
	void isFinishTile(bool);

	virtual spTile clone() {
		spTile tile = new Tile(this->getResAnim()->getName(), this->solid, this->getColumn(), this->getRow());
		return tile;
	}
	virtual spActor getEditLayout();
	virtual tinyxml2::XMLElement* getXML(Xml*); //! return an XML representation of the tile.
	virtual void setFromXML(XMLElement*); //! replace Tile properties with those provided in the XML.

	bool operator==(const Tile&) const;
	bool operator!=(const Tile&) const;
private:
	bool solid;

	bool isEntry = false;
	bool isFinish = false;
};
