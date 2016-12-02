#include "Play.h"
#include "Chest.h"
#include "GameOver.h"

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
						spMap nextMap = res::mapDao->getMap(to_string(map->getNextMapId()));
						gamePicker->setMap(nextMap);
						log::messageln("Show next map id %d", map->getNextMapId());
						init();
					}
					else {
						log::messageln("Game over");
						spGameOver gameOverScreen = new GameOver();
						flow::show(gameOverScreen);
					}
				}
				else {
					spTile facedTile = getFacedTile();
					Vector2 facedLocation = map->getTileLocation(facedTile);
					if (facedTile) {
						//check entities
						bool interacted = false;
						vector<spEntity> entities = map->getEntities();
						for (vector<spEntity>::iterator it = entities.begin(); it != entities.end(); ++it) {
							if ((*it)->getLocation() == facedLocation) {
								interacted = true;
								spEntity entity = *it;

								//if its a character, set from which way we are interacting
								spCharacter c = dynamic_cast<Character*>(&(*entity));
								if (c) {
									c->setInteractFrom(map->getDirectionFrom(c, character));
								}

								(*it)->interact();
								break;
							}
						}

						//interact with tile otherwise
						if (!interacted) {
							//if its a chest, set the character to interchange items with
							spChest chest = dynamic_cast<Chest*>(&(*facedTile));
							if (chest) {
								chest->setCharacter(character);
							}

							facedTile->interact();
						}
					}
				}
			}
		}
		else {
			once = false;
		}
	}
}

spTile Play::getFacedTile() {
	Vector2 location = map->getTileLocation(character);
	switch (character->getFacing()) {
	case Map::Direction::NORTH:
		return map->getTile(location.x, location.y - 1);
	case Map::Direction::EAST:
		return map->getTile(location.x + 1, location.y);
	case Map::Direction::SOUTH:
		return map->getTile(location.x, location.y + 1);
	case Map::Direction::WEST:
		return map->getTile(location.x - 1, location.y);
	}
	return nullptr;
}