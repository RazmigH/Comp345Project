#include "EditPane.h"

EditPane::EditPane(spTile t, spMap m) {
	this->tile = t;
	this->map = m;
}

EditPane::~EditPane() {

}

spEntity EditPane::getEntity() {
	vector<spEntity> entities = map->getEntities();
	for (vector<spEntity>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if ((*it)->getLocation() == map->getTileLocation(tile)) {
			return *it;
		}
	}
	return nullptr;
}