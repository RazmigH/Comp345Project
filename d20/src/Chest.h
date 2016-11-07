#pragma once
#include "Tile.h"
#include <vector>


DECLARE_SMART(Chest, spChest);
class Chest : public Tile {
public:
	enum ChestState {
		CLOSED, OPEN
	};
	Chest(ChestState = ChestState::OPEN);
	~Chest();
	spActor getEditLayout();
	spTile clone() {
		spChest tile = new Chest(state);
		return tile;
	}
private:
	ChestState state;
	//std::vector<Item> items;
};