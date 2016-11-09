#include <iostream>
#include "MapCreator.h"
#include "Map.h"
#include "TextButton.h"
#include "Chest.h"
#include "ImageResource.h" 
#include "MapDao.h" 
#include "MainMenu.h" 
#include "InputDialog.h"

MapCreator::MapCreator(spMap useMap){
	setName("Map Creator");
	addBackButton();

	this->currentAction = CreatorAction::SELECT;

	//tile selections
	const int tile_count = 5;

	//all tiles to appear in tile selection grid
	spChest closedChest = new Chest(Chest::ChestState::CLOSED);
	spChest openChest = new Chest(Chest::ChestState::OPEN);
	spTile tiles[tile_count] = {
		new Tile("blank"), 
		new Tile("grass"),
		new Tile("grass-border", true),
		closedChest,
		openChest
	};
	selected = tiles[0];

	//create container for tile selection grid
	spActor selectPane = new Actor();
	selectPane->setSize(150, 300);

	//create tile selection grid
	spGrid selectGrid = new Grid(1, tile_count);
	selectGrid->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectTileOption));

	//create buttons
	spTextButton fillBtn = new TextButton("fill");
	fillBtn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::fill));

	//add select button
	spTile select = new Tile("cursor");
	select->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectToolClicked));

	//add option tiles to grid
	for (int i = 0; i < tile_count; i++) {
		spTile tile = tiles[i];
		selectGrid->setTile(0, i, tile);
	}
	this->selections = selectGrid;

	//map
	this->map = useMap;
	map->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectMapTile));
	map->addEventListener(TouchEvent::MOVE, CLOSURE(this, &MapCreator::onMoveOnMap));

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

	//save button
	spTextButton save = new TextButton("Save");
	save->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::saveMap));

	//selection highlight
	highlight = new ColorRectSprite();
	highlight->setSize(Tile::TILE_SIZE, Tile::TILE_SIZE);
	highlight->setColor(Color::Red);
	highlight->setAlpha(50000);

	//top pane
	spActor topPane = new Actor();
	topPane->setHeight(50);
	spTextButton resetPoints = new TextButton("Reset pt.");
	resetPoints->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::resetPts));
	resetPoints->setWidth(100);

	//position selections
	selectPane->setPosition(0, topPane->getHeight());
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
	map->setPosition(selectPane->getWidth(), selectPane->getY());
	addChild(map);

	//position details pane
	detailsPane->setPosition(map->getX() + map->getWidth(), map->getY());

	detailsTitle->setPosition(0, 5);
	detailsTitle->setWidth(detailsPane->getWidth());
	detailsPane->addChild(detailsTitle);

	currentDetails->setPosition(0, detailsTitle->getY() + detailsTitle->getHeight() + 25);
	currentDetails->setWidth(detailsPane->getWidth());
	detailsPane->addChild(currentDetails);

	save->setPosition(detailsPane->getWidth() - save->getWidth() - 5, detailsPane->getHeight() - save->getHeight() - 10);
	detailsPane->addChild(save);

	addChild(detailsPane);

	//position top pane
	topPane->setWidth(this->calculateSize().x);
	resetPoints->setAnchor(0.5, 0.5);
	resetPoints->setPosition(topPane->getWidth() / 2, topPane->getHeight() / 2);
	topPane->addChild(resetPoints);
	addChild(topPane);

	//fit children
	fitToWindow(this, true);
}

MapCreator::~MapCreator() {

}

//Event handler for when a tile is clicked in the tile option select pane
void MapCreator::onSelectTileOption(Event* e) {
	this->currentAction = CreatorAction::TILE_EDIT;
	selected = selections->getTile(e);
	cout << "Selected " << selected->getName() << endl;
}

//event handler for when the select tool is selected
void MapCreator::onSelectToolClicked(Event* e) {
	this->currentAction = CreatorAction::SELECT;
	cout << "Select Tool selected" << selected->getName() << endl;
}

//Event handler for when a tile on the map is clicked
void MapCreator::onSelectMapTile(Event* e) {
	spTile tile = map->getTile(e);
	if (this->currentAction == CreatorAction::TILE_EDIT && *tile != *selected) {
		spTile newTile = selected->clone();
		map->setTile(map->getTileLocation(tile), newTile);
	}
	else if (this->currentAction == CreatorAction::SELECT) {
		Vector2 loc = map->getTileLocation(tile);
		if (loc == map->getTileLocation(highlight)) {
			if (highlight->getParent() == (spActor)map)
				map->removeChild(highlight);
			if (currentDetails->getParent() == (spActor)detailsPane)
				detailsPane->removeChild(currentDetails);
			highlight->setPosition(highlight->getX() - 100, highlight->getY() - 100); //invalidate hack
		}
		else {
			map->addToGrid(highlight, loc.x, loc.y);
			if (currentDetails->getParent() == (spActor)detailsPane)
				detailsPane->removeChild(currentDetails);
			currentDetails = tile->getEditLayout();
			currentDetails->setPosition(0, detailsTitle->getY() + detailsTitle->getHeight() + 25);
			//currentDetails->setWidth(detailsPane->getWidth());
			detailsPane->addChild(currentDetails);
		}
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

void MapCreator::resetPts(Event* e) {
	for (int r = 0; r < map->getRows(); r++) {
		for (int c = 0; c < map->getCols(); c++) {
			spTile tile = map->getTile(c, r);
			tile->isEntryTile(false);
			tile->isFinishTile(false);
		}
	}
	cout << "Entry and Exit points were reset to default." << endl;
}

void MapCreator::saveMap(Event* e) {
	spInputDialog input = new InputDialog("Enter Map Name", map->getName());
	flow::show(input, [=](Event*) {
		MapDao* dao = new MapDao();
		map->setName(input->getText());
		dao->addMap(map);
		delete(dao);
		cout << "Saved map" << endl;
	});
}