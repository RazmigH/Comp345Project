#pragma once
#include "Tile.h"
#include <vector>


DECLARE_SMART(Chest, spChest);
class Chest : public Tile {
public:
	enum ChestState {
		CLOSED, OPEN
	};

	static const string IDENTIFIER;

	Chest(ChestState = ChestState::OPEN);
	~Chest();
	ChestState getState();
	void setState(ChestState);

	spTile clone() {
		spChest tile = new Chest(state);
		return tile;
	}
	tinyxml2::XMLElement* getXML(Xml*);
	static spTile getFromXML(XMLElement*);
	string getIdentifier();
private:
	ChestState state;
	//std::vector<Item> items;
};