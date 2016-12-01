#include "MapCreator.h"
#include "Map.h"
#include "TextButton.h"
#include "Chest.h"
#include "GameResource.h"
#include "MainMenu.h" 
#include "InputDialog.h"
#include "DefaultEditPane.h"
#include "ChestEditPane.h"
#include "Chest.h"

MapCreator::MapCreator(spMapPicker useMap){
	mapSource = useMap;
}

void MapCreator::init() {
	setName("Map Creator");
	addBackButton();

	this->currentAction = CreatorAction::SELECT;

	//tile selections
	const int tile_count = 5;

	//all tiles to appear in tile selection grid
	spChest closedChest = new Chest(Chest::ChestState::CLOSED);
	spChest openChest = new Chest(Chest::ChestState::OPEN);
	spTile tiles[tile_count+1] = { 
		new Tile("cursor"),
		new Tile("blank"),
		new Tile("grass"),
		new Tile("grass-border", true),
		closedChest,
		openChest
	};
	selectedOption = tiles[1];

	//top pane
	topPane = new Actor();
	topPane->setHeight(50);
	addChild(topPane);

	//create container for tile selection grid
	selectPane = new Actor();
	selectPane->setPosition(0, topPane->getHeight());

	//create tile selection grid
	selectGrid = new Grid(1, tile_count);
	selectGrid->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectTileOption));
	selectGrid->setAnchor(0.5, 0.5);
	selectPane->addChild(selectGrid);

	//create buttons
	fillBtn = new TextButton("fill");
	fillBtn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::fill));
	fillBtn->setAnchor(0.5, 0.5);
	selectPane->addChild(fillBtn);

	addChild(selectPane);

	//add option tiles to grid
	for (int i = 0; i < tile_count; i++) {
		spTile tile = tiles[i];
		selectGrid->setTile(0, i, tile);
	}
	this->selections = selectGrid;

	//map
	this->map = mapSource->getMap();
	map->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::onSelectMapTile));
	map->addEventListener(TouchEvent::MOVE, CLOSURE(this, &MapCreator::onMoveOnMap));
	addChild(map);

	//details pane
	detailsPane = new Actor();
	currentDetails = new Actor();

	detailsTitle = new TextField();
	detailsTitle->setAnchor(0.5, 0.5);
	detailsTitle->setText("Current Selection");
	detailsTitle->setFont(res::resources.getResFont("font"));
	detailsTitle->setHAlign(TextStyle::HALIGN_MIDDLE);

	//save button
	save = new TextButton("Save");
	save->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MapCreator::saveMap));

	detailsPane->addChild(detailsTitle);
	detailsPane->addChild(currentDetails);
	detailsPane->addChild(save);
	addChild(detailsPane);

	//selection highlight
	highlight = new ColorRectSprite();
	highlight->setColor(Color::Red);
	highlight->setAlpha(50000);
	map->addChild(highlight);
}

MapCreator::~MapCreator() {

}

//Event handler for when a tile is clicked in the tile option select pane
void MapCreator::onSelectTileOption(Event* e) {
	spTile t = selections->getTile(e);
	if (selections->getTileLocation(t) == Vector2(0, 0)) {
		this->currentAction = CreatorAction::SELECT;
		log::messageln("Selected Tool selected %s", selectedOption->getName());
	}
	else {
		this->currentAction = CreatorAction::TILE_EDIT;
		selectedOption = t;
		log::messageln("Selected %s", selectedOption->getName());
	}
}

//Event handler for when a tile on the map is clicked
void MapCreator::onSelectMapTile(Event* e) {
	spTile tile = map->getTile(e);
	if (this->currentAction == CreatorAction::TILE_EDIT && *tile != *selectedOption) {
		spTile newTile = selectedOption->clone();
		map->setTile(map->getTileLocation(tile), newTile);
	}
	else if (this->currentAction == CreatorAction::SELECT) {
		if (selectedTile && tile->getPosition() == selectedTile->getPosition()) {
			if (currentDetails->getParent() == (spActor)detailsPane)
				detailsPane->removeChild(currentDetails);
			selectedTile = nullptr;
		}
		else {
			if (currentDetails->getParent() == (spActor)detailsPane)
				detailsPane->removeChild(currentDetails);
			currentDetails = getEditPane(tile);// tile->getEditLayout();
			detailsPane->addChild(currentDetails);
			selectedTile = tile;
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
	map->setTiles(selectedOption);
}

void MapCreator::saveMap(Event* e) {
	//validate
	//check all tiles set
	for (int c = 0; c < map->getCols(); c++) {
		for (int r = 0; r < map->getRows(); r++) {
			spTile tile = map->getTile(c, r);
			if (tile->getImageName() == "transparent" || tile->getImageName() == "blank") {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Map", "You can't leave empty tiles in your map!", NULL);
				return;
			}
		}
	}

	//check valid path
	log::messageln("Start looking");
	vector<string> directions = map->findPath(map->getTile(map->getEntryPoint()), map->getTile(map->getExitPoint()));
	log::messageln("done looking");

	//print path for fun, can remove.
	for (vector<string>::iterator it = directions.begin(); it != directions.end(); ++it) {
		string s = *it;
		log::message("%s, ", s.c_str());
	}
	if (directions.empty()) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Map", "The player must be able to reach the finish point!", NULL);
		return;
	}

	if (map->getEntryPoint() == map->getExitPoint()) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Map", "The entrance and exit of the map must be in different places!", NULL);
		return;
	}

	//map is valid, save it
	spInputDialog input = new InputDialog("Enter Map Name", map->getName());
	flow::show(input, [=](Event*) {
		map->setName(input->getText());
		res::mapDao->addMap(map);
		log::messageln("saved map");
	});
}

void MapCreator::update() {
	Layout::update();
	setSize(getStage()->getSize());

	selectPane->setSize(getWidth() * 0.15, getHeight());
	selectGrid->setWidth(selectPane->getWidth() * 0.35);
	selectGrid->setHeight(selectGrid->getWidth() * selectGrid->getRows());
	selectGrid->setPosition(selectPane->getWidth() / 2, selectPane->getHeight() * 0.3);
	fillBtn->setPosition(selectGrid->getX(), selectGrid->getY() + selectGrid->getHeight() / 2 + 25);

	map->setWidth(getWidth() * 0.7);
	map->setHeight(map->getTileWidth() * map->getRows());
	map->setPosition(selectPane->getX() + selectPane->getWidth(), selectPane->getY());
	highlight->setSize(map->getTileWidth(), map->getTileHeight());
	if (selectedTile) {
		highlight->setPosition(selectedTile->getPosition());
	}
	else {
		highlight->setPosition(-1000, -1000);
	}

	detailsPane->setSize(getWidth() * 0.15, getHeight());
	detailsPane->setPosition(map->getX() + map->getWidth(), map->getY());
	detailsTitle->setPosition(detailsPane->getWidth() / 2, 5);
	detailsTitle->setFontSize(getWidth() / 50);
	detailsTitle->setHeight(getWidth() / 50);
	currentDetails->setPosition(0, detailsTitle->getY() + detailsTitle->getHeight() + 25);
	currentDetails->setWidth(detailsPane->getWidth());
	currentDetails->setHeight(detailsPane->getHeight() - currentDetails->getY());

	save->setPosition(detailsPane->getWidth() - save->getWidth() - 5, detailsPane->getHeight() - save->getHeight() - 55);

	topPane->setWidth(getWidth());
}

spEditPane MapCreator::getEditPane(spTile tile) {
	spEditPane pane;

	if (tile->getIdentifier() == Chest::IDENTIFIER) {
		spChest chest = dynamic_cast<Chest*>(&(*tile));
		if(chest)
			pane = new ChestEditPane(chest, map);
	}


	if (!pane) {
		pane = new DefaultEditPane(tile, map);
	}
	return pane;
}