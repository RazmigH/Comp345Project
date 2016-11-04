#include <iostream>
#include "Play.h"
#include "Map.h"
#include "CharacterDisplay.h"

Play::Play(){
	spCharacterDisplay sc = new CharacterDisplay();
	sc->setSize(96, 640);
	sc->setPosition(0, 96);

	spMap map = new Map();
	map->setPosition(96, 96);
	
	
	this->map = map;


	this->setSize(832, 480);


	//center grid in container
	//sc->setPosition(this->getWidth() / 2, this->getHeight() / 2);

	addChild(sc);
	addChild(map);
	//fit children
	//setSize(this->calculateSize());
}
Play::~Play() {

}
