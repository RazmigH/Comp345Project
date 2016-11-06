#include "Chest.h"
#include "ChestEditPane.h"
Chest::Chest(ChestState state) : MapTile("chests", true, (state == ChestState::CLOSED ? 1 : 0), 0), state(state) {
}

Chest::~Chest() {

}

spActor Chest::getEditLayout() {
	spChestEditPane actor = new ChestEditPane(this);
	return actor;
}