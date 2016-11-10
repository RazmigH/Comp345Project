#include <iostream>
#include "Play.h"
#include "Map.h"
#include "CharacterDisplay.h"
#include "InventoryDisplay.h"
#include "MainMenu.h" 


Play::Play(){

}

void Play::init() {
	setName("Play Layout");
	addBackButton();

	spCharacterDisplay sc = new CharacterDisplay();
	sc->setSize(96, 320);
	sc->setPosition(0, 96);

	spMap map = new Map();
	map->setPosition(96, 96);
	map->setTiles(new Tile("grass"));


	spInventoryDisplay iDisplay = new InventoryDisplay();
	iDisplay->setSize(96, 320);
	iDisplay->setPosition(736, 96);

	this->map = map;

	this->setSize(832, 480);

	//center grid in container
	//sc->setPosition(this->getWidth() / 2, this->getHeight() / 2);

	addChild(sc);
	addChild(map);
	addChild(iDisplay);
	//fit children
	fitToWindow();
}

Play::~Play() {

}
