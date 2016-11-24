#include "GamePicker.h"
#include "GameResource.h"

GamePicker::GamePicker() {
	characterPicker = new CharacterPicker();
	mapPicker = new MapPicker();

	mapBtn = new TextButton("Map");
	mapBtn->setAnchor(0.5, 0.5);
	mapBtn->addClickListener([=](Event*) {
		flow::show(mapPicker, [=](Event*) {
			init();
		});
	});

	charBtn = new TextButton("Player");
	charBtn->setAnchor(0.5, 0.5);
	charBtn->addClickListener([=](Event*) {
		flow::show(characterPicker, [=](Event*) {
			init();
		});
	});

	mapText = new TextField();
	mapText->setFont(res::resources.getResFont("font"));
	mapText->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
	mapText->setAnchor(0.5, 0.5);

	characterText = new TextField();
	mapText->setFont(res::resources.getResFont("font"));
	characterText->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
	characterText->setAnchor(0.5, 0.5);

	okbtn = new TextButton("Ok");
	okbtn->addEventListener(TouchEvent::CLICK, [=](Event*) {
		if (getMap() && getCharacter() && getNext()) {
			getNext()->init();
			flow::show(getNext(), [=](Event*) {
				init();
			});
		}
	});

	init();
}

GamePicker::~GamePicker() {

}

void GamePicker::init() {
	clear();

	mapPicker->init();
	characterPicker->init();

	mapText->setText(mapPicker->getMap() ? mapPicker->getMap()->getName() : "-");
	characterText->setText(characterPicker->getCharacter() ? characterPicker->getCharacter()->getName() : "-");

	addChild(mapBtn);
	addChild(charBtn);
	addChild(okbtn);
	addChild(mapText);
	addChild(characterText);
	addBackButton();
}

spMap GamePicker::getMap() {
	return mapPicker->getMap();
}

spCharacter GamePicker::getCharacter() {
	return characterPicker->getCharacter();
}

void GamePicker::setMap(spMap m) {
	mapPicker->setMap(m);
}
void GamePicker::setCharacter(spCharacter c) {
	characterPicker->setCharacter(c);
}

void GamePicker::update() {
	Layout::update();
	setSize(getStage()->getSize());

	mapBtn->setPosition(getWidth() * 0.25, getHeight() / 2);
	charBtn->setPosition(getWidth() * 0.75, getHeight() / 2);
	okbtn->setPosition(getWidth() - okbtn->getWidth() - 5, getHeight() - okbtn->getHeight() - 5);

	mapText->setPosition(mapBtn->getX(), mapBtn->getY() + mapBtn->getHeight() + 10);
	mapText->setFontSize(getHeight()  / 15);
	characterText->setPosition(charBtn->getX(), charBtn->getY() + charBtn->getHeight() + 10);
	characterText->setFontSize(getHeight() / 15);
}