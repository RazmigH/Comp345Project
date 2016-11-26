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

	character->setLocation(start.x, start.y);
	map->addEntity(character);
	//map->addToGrid(character, start.x, start.y);

	//inventory = inventoryDao->getInventory(character->getInvID);
	iDisplay = new InventoryDisplay(character);

	addChild(sc);
	addChild(map);
	addChild(iDisplay);
	addBackButton();
}

Play::~Play() {
	
}

void Play::update() {
	Layout::update();
	setSize(getStage()->getSize());

	sc->setSize(getWidth() * 0.2, getHeight());
	sc->setPosition(0, 40);

	map->setWidth(getWidth() * 0.6);
	map->setHeight(map->getTileWidth() * map->getRows());
	map->setPosition(sc->getX() + sc->getWidth(), sc->getY());

	iDisplay->setSize(getWidth() * 0.2, getHeight());
	iDisplay->setPosition(map->getX() + map->getWidth(), map->getY());

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
			if (!once) {
				once = true;
				if (map->getTileLocation(character) == map->getExitPoint()) {
					if (map->getNextMapId() != -1 &&
						character->getFirstTween() == NULL) {
						//improve 
						gamePicker->setMap(res::mapDao->getMap(to_string(map->getNextMapId())));
						log::messageln("Show next map id %d", map->getNextMapId());
						init();
					}
					else {
						log::messageln("Game over");
					}
				}
			}
		}
		else {
			once = false;
		}
	}
}