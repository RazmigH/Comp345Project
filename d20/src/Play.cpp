#include <iostream>
#include "Play.h"
#include "Map.h"
#include "CharacterDisplay.h"

Play::Play(){
	spCharacterDisplay sc = new CharacterDisplay();
	sc->setSize(128, 640);
	sc->setPosition(0, 128);


	spCharacterDisplay sc2 = new CharacterDisplay();
	sc->setSize(128, 640);
	sc->setPosition(768, 128);

	this->setSize(896, 896);


	//center grid in container
	//sc->setPosition(this->getWidth() / 2, this->getHeight() / 2);

	addChild(sc);
	//fit children
	//setSize(this->calculateSize());
}
Play::~Play() {

}
