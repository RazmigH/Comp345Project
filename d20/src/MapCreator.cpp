#include <iostream>
#include "MapCreator.h"
#include "Map.h"

MapCreator::MapCreator() {
	spMap map = new Map();
	addChild(map);
	setSize(map->getSize());
}
MapCreator::~MapCreator() {

}