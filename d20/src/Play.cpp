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

	Vector2 start = map->getEntryPoint();
	map->addToGrid(character, start.x, start.y);

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

void Play::update() {
	if (character && map) {
		Vector2 charLoc = map->getTileLocation(character);
		const Uint8* data = SDL_GetKeyboardState(NULL);
		if (data[SDL_GetScancodeFromKey(SDLK_w)]) {
			character->setUp();
			map->move(character, charLoc.x, charLoc.y - 1);
		}
		else if (data[SDL_GetScancodeFromKey(SDLK_s)]) {
			character->setDown();
			map->move(character, charLoc.x, charLoc.y + 1);
		}
		else if (data[SDL_GetScancodeFromKey(SDLK_a)]) {
			character->setLeft();
			map->move(character, charLoc.x - 1, charLoc.y);
		}
		else if (data[SDL_GetScancodeFromKey(SDLK_d)]) {
			character->setRight();
			map->move(character, charLoc.x + 1, charLoc.y);
		}
		else if (data[SDL_GetScancodeFromKey(SDLK_SPACE)]) {
			//interact();
		}
	}
}