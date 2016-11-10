#include <iostream>
#include "Play.h"

Play::Play(spGamePicker picker){
	setName("Play Layout");

	gamePicker = picker;
}

void Play::init() {
	clear();

	character = gamePicker->getCharacter();
	sc = new CharacterDisplay(character);

	map = gamePicker->getMap();

	//inventory = inventoryDao->getInventory(character->getInvID);
	spInventoryDisplay iDisplay = new InventoryDisplay();

	sc->setSize(96, 320);
	sc->setPosition(0, 40);

	map->setPosition(sc->getWidth(), sc->getY());

	iDisplay->setSize(96, 320);
	iDisplay->setPosition(map->getX() + map->getWidth(), map->getY());

	addChild(sc);
	addChild(map);
	addChild(iDisplay);
	addBackButton();

	fitToWindow(true);
}

Play::Play()
{
}

Play::~Play() {

}
