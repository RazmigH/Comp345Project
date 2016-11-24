#include "CharacterPicker.h"
#include "GameResource.h"

CharacterPicker::CharacterPicker(string message) {
	title = new TextField();
	title->setText(message);
	title->setFont(res::resources.getResFont("font"));
	title->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);

	highlight = new ColorRectSprite();
	highlight->setColor(Color::Lime);
	highlight->setAlpha(30000);

	init();
}

void CharacterPicker::init() {
	setName("CharacterPicker");

	okbtn = new TextButton("Ok");
	okbtn->addEventListener(TouchEvent::CLICK, [=](Event*) {
		if (characterId != "" && getNext()) {
			getNext()->init();
			flow::show(getNext(), [=](Event*) {
				load();
			});
		}
		finish();
	});

	empty = new Tile("transparent");
	grid = new DynamicGrid(4, 10, empty);
	grid->addClickListener(CLOSURE(this, &CharacterPicker::onSelectCharacter));

	highlight->setPosition(-100, -100);
	grid->addChild(highlight);

	load();
}

void CharacterPicker::update() {
	Layout::update();
	setSize(getStage()->getSize());

	title->setPosition(getWidth() / 2 - title->getWidth() / 2, 10);
	title->setFontSize(getHeight() / 20);
	title->setHeight(getHeight() / 20);

	okbtn->setPosition(getWidth() - okbtn->getWidth() - 5, getHeight() - okbtn->getHeight() - 5);
	grid->setPosition(getWidth() / 2 - grid->getWidth() / 2, title->getY() + title->getHeight() + 5);
	grid->setWidth(getWidth() / 3);
	grid->setHeight(grid->getTileWidth() * grid->getRows());

	if (selected) {
		log::messageln("moving highlight %d %d", selected->getX(), selected->getY());
		highlight->setSize(grid->getTileWidth(), grid->getTileHeight());
		highlight->setPosition(selected->getPosition());
	}
}

CharacterPicker::~CharacterPicker() {

}

void CharacterPicker::load() {
	this->clear();

	addBackButton();
	addChild(title);
	addChild(okbtn);
	grid->clear();

	vector<spCharacter> characters = res::characterDao->getCharacters();
	for (vector<spCharacter>::iterator it = characters.begin(); it != characters.end(); ++it) {
		spCharacter temp = *it;
		grid->add(temp);
		grid->getLast()->setName(to_string(temp->getId()));
	}
	grid->addChild(highlight);
	addChild(grid);
}

void CharacterPicker::onSelectCharacter(Event* e) {
	spTile tile = grid->getTile(e);
	characterId = tile->getName();
	selected = tile;
}

spCharacter CharacterPicker::getCharacter() {
	return res::characterDao->getCharacter(characterId);
}
void CharacterPicker::setCharacter(spCharacter c) {
	characterId = c->getId();
}