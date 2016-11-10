#include <iostream>
#include "MainMenu.h"
#include "MapPicker.h"
#include "MapCreator.h"
#include "CharacterPicker.h"
#include "Play.h"

MainMenu::MainMenu() {
	setName("Main Menu");

	//Place wanted menu options here
	//Don't forget to add respective click handler (onClick())
	const string menuTexts[] = {
		"Play",
		"Create a map",
		"add wtv"
	};

	//title text
	title = createTextField("D20 Game");
	title->setFontSize(40);

	//create menu option textfields
	for (int i = 0; i < menu_size; i++) {
		//create textfield
		spTextField textfield = createTextField(menuTexts[i]);
		textfield->addClickListener(CLOSURE(this, &MainMenu::onClick));
		menuItems.push_back(textfield);
	}

	getStage()->setSize(400, menu_size * 100);
	init();
}

void MainMenu::init() {
	this->clear();
	setSize(getStage()->getSize());

	title->setPosition(getWidth() / 2, 50);
	addChild(title);

	int i = 0;
	for (vector<spTextField>::iterator it = menuItems.begin(); it != menuItems.end(); ++it) {
		spTextField textfield = *it;
		textfield->setPosition(getWidth() / 2, title->getPosition().y + (((i++) + 1) * 50));
		addChild(textfield);
	}

	fitToWindow(this);
}

void MainMenu::onClick(Event* e) {
	if (e->target->getName() == "Play") {
		cout << "play" << endl;
		spCharacterPicker picker = new CharacterPicker();
		spPlay play = new Play();
		picker->setNext(play);
		show(picker, [=](Event*) {
			init();
		});
		//resize window to fit layout
		//SDL_SetWindowSize(getStage()->getAssociatedWindow(), getStage()->getWidth(), getStage()->getHeight());
	}
	else if (e->target->getName() == "Create a map") {
		cout << "Create" << endl;
		spMapPicker mapPicker = new MapPicker();
		spMapCreator creator = new MapCreator(mapPicker);
		mapPicker->setNext(creator);
		show(mapPicker, [=](Event*) {
		});
	}
	else if (e->target->getName() == "add wtv") {
		cout << "add" << endl;
	}
}

MainMenu::~MainMenu() {

}

//method to create and style a menu option textfield
spTextField MainMenu::createTextField(string text) {
	spTextField temp = new TextField();
	temp->setText(text);
	temp->setColor(Color::White);
	temp->setFontSize(30);
	temp->setAnchor(0.5, 0.5);
	temp->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
	temp->setName(text);
	return temp;
}
