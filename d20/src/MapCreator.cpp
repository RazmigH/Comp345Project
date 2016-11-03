#include <iostream>
#include "MapCreator.h"
#include "Map.h"
#include "TextButton.h"

MapCreator::MapCreator(){
	//tile selections
	const int tile_count = 5;

	//all tiles to appear in tile selection grid
	spTile tiles[tile_count] = {
		new Tile(), 
		new Tile("grass"),
		new Tile("grass-border"),
		new Tile("chests", 0, 1),
		new Tile("chests", 0, 0),
	};
	selected = tiles[0];

	//create container for tile selection grid
	spActor selectPane = new Actor();

	//create tile selection grid
	spGrid selectGrid = new Grid(tile_count, 1);
	selectGrid->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectTileOption));

	//create buttons
	spTextButton fillBtn = new TextButton("fill");
	fillBtn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::fill));

	//add option tiles to grid
	for (int i = 0; i < tile_count; i++) {
		spTile tile = tiles[i];
		selectGrid->setTile(i, 0, tile);
	}
	this->selections = selectGrid;

	//map
	spMap map = new Map();
	map->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectMapTile));
	map->addEventListener(TouchEvent::MOVE, CLOSURE(this, &MapCreator::onMoveOnMap));
	this->map = map;

	//position selections
	selectPane->setSize(150, 300);
	selectGrid->setAnchor(0.5, 0.5);
	selectGrid->setPosition(selectPane->getWidth() / 2, selectPane->getHeight() / 2);

	//position buttons
	fillBtn->setAnchor(0.5, 0.5);
	fillBtn->setPosition(selectGrid->getX(), selectGrid->getY() + selectGrid->getHeight()/2 + 25);

	selectPane->addChild(fillBtn);
	selectPane->addChild(selectGrid);
	addChild(selectPane);


	//position map
	map->setPosition(selectPane->getWidth(), 0);
	addChild(map);


	//fit children
	setSize(this->calculateSize());
}
MapCreator::~MapCreator() {

}

//Event handler for when a tile is clicked in the tile option select pane
void MapCreator::onSelectTileOption(Event* e) {
	TouchEvent* te = safeCast<TouchEvent*>(e);
	Vector2 pos = te->localPosition;
	selected = selections->getTile(selections->getTileLocation(pos));
	cout << "Selected " << selected->getName() << endl;
}

//Event handler for when a tile on the map is clicked
void MapCreator::onSelectMapTile(Event* e) {
	TouchEvent* te = safeCast<TouchEvent*>(e);
	Vector2 pos = te->localPosition;

	Vector2 tileLoc = map->getTileLocation(pos);
	spTile oldTile = map->getTile(tileLoc);
	if (*oldTile != *selected) {
		spTile newTile = new Tile(selected);
		map->setTile(tileLoc, newTile);
	}
}

void MapCreator::onMoveOnMap(Event* e) {
	TouchEvent* te = safeCast<TouchEvent*>(e);
	if(te->getPointer()->isPressed())
		onSelectMapTile(e);
}

void MapCreator::fill(Event* e) {
	cout << "fill" << endl;
	map->setTiles(selected);
}