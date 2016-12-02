#include "MainMenu.h"
#include "MapPicker.h"
#include "MapCreator.h"
#include "GamePicker.h"
#include "Play.h"
#include "GameResource.h"

/*
Memory leaks
- leadTo variable in Layout (20) (biggest problem, might be due to oxygine-flow)
	-> mapPicker->dao->getMap inclickhandler (depends on mapsize)
- the two getResAnim/getResFont in TextButton.cpp (2)
- transition.cpp clear() OX_ASSERT(!"not implemented");
*/
MainMenu::MainMenu() {
	setName("Main Menu");

	//Place wanted menu options here
	//Don't forget to add respective click handler (onClick())
	const string menuTexts[] = {
		"Play", 
		"Create a map",
		"(more coming soon)"
	};

	//title text
	title = createTextField("D20 Game");
	title->setFont(res::resources.getResFont("font"));
	addChild(title);

	//create menu option textfields
	for (int i = 0; i < menu_size; i++) {
		//create textfield
		spTextField textfield = createTextField(menuTexts[i]);
		textfield->setFont(res::resources.getResFont("font"));
		textfield->addClickListener(CLOSURE(this, &MainMenu::onClick));
		menuItems.push_back(textfield);
		addChild(textfield);
	}
}

void MainMenu::onClick(Event* e) {
	if (e->target->getName() == "Play") {
		log::messageln("Play");
		spGamePicker picker = new GamePicker();
		spPlay play = new Play(picker);
		picker->setNext(play);
		show(picker, [=](Event*) {
			init();
		});
	}
	else if (e->target->getName() == "Create a map") {
		log::messageln("Create Map");
		spMapPicker mapPicker = new MapPicker();
		spMapCreator creator = new MapCreator(mapPicker);
		mapPicker->setNext(creator);
		show(mapPicker, [=](Event*) {
			init();
		});
		mapPicker->getObjectID();
	}
	else if (e->target->getName() == "add wtv") {
		log::messageln("add wtv");
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

void MainMenu::update() {
	Layout::update();
	setSize(getStage()->getSize());

	title->setPosition(getWidth() / 2, getHeight() / 6);
	title->setFontSize((getHeight() / 10) * 1.30);
	title->setHeight((getHeight() / 10) * 1.30);

	spTextField previous = title;
	for (vector<spTextField>::iterator it = menuItems.begin(); it != menuItems.end(); ++it) {
		(*it)->setPosition(getWidth() / 2, previous->getY() + previous->getHeight() + 15);
		(*it)->setFontSize(getHeight() / 10);
		(*it)->setHeight(getHeight() / 10);
		previous = *it;
	}
}