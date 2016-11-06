#include <iostream>
#include "MapCreator.h"
#include "Map.h"
#include "TextButton.h"
#include "Chest.h"
#include "ImageResource.h" 

MapCreator::MapCreator(){
	//tile selections
	const int tile_count = 5;

	//all tiles to appear in tile selection grid
	spChest closedChest = new Chest(ChestState::CLOSED);
	spChest openChest = new Chest(ChestState::OPEN);
	spMapTile tiles[tile_count] = {
		new MapTile(), 
		new MapTile("grass"),
		new MapTile("grass-border"),
		closedChest,
		openChest
	};
	selected = tiles[0];

	//create container for tile selection grid
	spActor selectPane = new Actor();
	selectPane->setSize(150, 300);

	//create tile selection grid
	spGrid selectGrid = new Grid(tile_count, 1);
	selectGrid->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectTileOption));

	//create buttons
	spTextButton fillBtn = new TextButton("fill");
	fillBtn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::fill));

	//add select button
	spTile select = new Tile("cursor");
	select->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectToolClicked));

	//add option tiles to grid
	for (int i = 0; i < tile_count; i++) {
		spMapTile tile = tiles[i];
		selectGrid->setTile(i, 0, tile);
	}
	this->selections = selectGrid;

	//map
	spMap map = new Map(5, 5);
	map->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectMapTile));
	map->addEventListener(TouchEvent::MOVE, CLOSURE(this, &MapCreator::onMoveOnMap));
	this->map = map;

	//details pane
	detailsPane = new Actor();
	detailsPane->setSize(selectPane->getWidth(), selectPane->getHeight());

	detailsTitle = new TextField();
	detailsTitle->setText("Current Selection");
	TextStyle style;
	style.font = res::resources.getResFont("small");
	style.color = Color::White;
	style.vAlign = TextStyle::VALIGN_MIDDLE;
	style.hAlign = TextStyle::HALIGN_CENTER;
	detailsTitle->setStyle(style);

	currentDetails = new Actor();

	//position selections
	selectGrid->setAnchor(0.5, 0.5);
	selectGrid->setPosition(selectPane->getWidth() / 2, selectPane->getHeight() / 2);

	//position buttons
	fillBtn->setAnchor(0.5, 0.5);
	fillBtn->setPosition(selectGrid->getX(), selectGrid->getY() + selectGrid->getHeight()/2 + 25);

	//position select 
	select->setAnchor(0.5, 0.5);
	select->setPosition(selectGrid->getX(), selectGrid->getY() - selectGrid->getHeight() / 2 - 25);

	selectPane->addChild(fillBtn);
	selectPane->addChild(selectGrid);
	selectPane->addChild(select);
	addChild(selectPane);

	//position map
	map->setPosition(selectPane->getWidth(), 0);
	addChild(map);

	//position details pane
	detailsPane->setPosition(map->getX() + map->getWidth(), 0);

	detailsTitle->setPosition(0, 5);
	detailsTitle->setWidth(detailsPane->getWidth());
	detailsPane->addChild(detailsTitle);

	currentDetails->setPosition(0, detailsTitle->getY() + detailsTitle->getHeight() + 25);
	currentDetails->setWidth(detailsPane->getWidth());
	detailsPane->addChild(currentDetails);

	addChild(detailsPane);

	//fit children
	setSize(this->calculateSize());
}
MapCreator::~MapCreator() {

}

//Event handler for when a tile is clicked in the tile option select pane
void MapCreator::onSelectTileOption(Event* e) {
	this->currentAction = CreatorAction::TILE_EDIT;
	TouchEvent* te = safeCast<TouchEvent*>(e);
	Vector2 pos = te->localPosition;
	selected = selections->getTile(selections->getTileLocation(pos));
	cout << "Selected " << selected->getName() << endl;
}

//event handler for when the select tool is selected
void MapCreator::onSelectToolClicked(Event* e) {
	this->currentAction = CreatorAction::SELECT;
}

//Event handler for when a tile on the map is clicked
void MapCreator::onSelectMapTile(Event* e) {
	TouchEvent* te = safeCast<TouchEvent*>(e);
	Vector2 pos = te->localPosition;

	Vector2 tileLoc = map->getTileLocation(pos);
	spTile tile = map->getTile(tileLoc);
	if (this->currentAction == CreatorAction::TILE_EDIT && *tile != *selected) {
		spTile newTile = selected->clone();
		map->setTile(tileLoc, newTile);
	}
	else if (this->currentAction == CreatorAction::SELECT) {
		detailsPane->removeChild(currentDetails);
		currentDetails = tile->getEditLayout();
		currentDetails->setPosition(0, detailsTitle->getY() + detailsTitle->getHeight() + 25);
		//currentDetails->setWidth(detailsPane->getWidth());
		detailsPane->addChild(currentDetails);
	}
}

void MapCreator::onMoveOnMap(Event* e) {
	if (this->currentAction == CreatorAction::TILE_EDIT) {
		TouchEvent* te = safeCast<TouchEvent*>(e);
		if(te->getPointer()->isPressed())
			onSelectMapTile(e);
	}
}

void MapCreator::fill(Event* e) {
	cout << "fill" << endl;
	map->setTiles(selected);
}