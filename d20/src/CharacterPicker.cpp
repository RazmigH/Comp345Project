#include "CharacterPicker.h"

CharacterPicker::CharacterPicker(string message) {
	title = new TextField();
	title->setText(message);
	title->setColor(Color::White);
	title->setFontSize(18);
	title->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
	title->setHeight(30);
	init();
}

void CharacterPicker::init() {
	setName("CharacterPicker");

	okbtn = new TextButton("Ok");
	okbtn->addEventListener(TouchEvent::CLICK, [=](Event*) {
		cout << "INININNININN " << (character ? 1 : 0) << (getNext() ? 1 : 0) << endl;
		if (character && getNext()) {
			cout << "ABABABABABABABB" << endl;
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

	highlight = new ColorRectSprite();
	highlight->setSize(Tile::TILE_SIZE, Tile::TILE_SIZE);
	highlight->setColor(Color::Lime);
	highlight->setAlpha(30000);
	highlight->setPosition(-100, -100);

	load();
}

CharacterPicker::~CharacterPicker() {

}

void CharacterPicker::load() {
	this->clear();

	setSize(getStage()->getSize());
	addBackButton();
	title->setPosition(getWidth() / 2 - title->getWidth() / 2, 10);
	addChild(title);
	okbtn->setPosition(getWidth() - okbtn->getWidth() - 5, getHeight() - okbtn->getHeight() - 5);
	addChild(okbtn);
	grid->clear();
	grid->setPosition(getWidth() / 2 - grid->getWidth() / 2, title->getY() + title->getHeight() + 5);

	dao = new CharacterDao();
	vector<spCharacter> characters = dao->getCharacters();
	for (vector<spCharacter>::iterator it = characters.begin(); it != characters.end(); ++it) {
		spCharacter temp = *it;
		grid->add(temp);
		grid->getLast()->setName(to_string(temp->getId()));
	}
	addChild(grid);

	fitToWindow(true);
}

void CharacterPicker::onSelectCharacter(Event* e) {
	spTile tile = grid->getTile(e);
	if (*tile != *empty && tile->getPosition() != highlight->getPosition()) {
		Vector2 tileLoc = grid->getTileLocation(tile);
		grid->addToGrid(highlight, tileLoc.x, tileLoc.y);
		character = dao->getCharacter(tile->getName());
		if(character)
		character->printStats();
	}
}

spCharacter CharacterPicker::getCharacter() {
	return character;
}
