#include <iostream>
#include "MainMenu.h"
#include "MapCreator.h"

MainMenu::MainMenu() {
	//Amount of menu options
	const int menu_size = 3;

	//Place wanted menu options here
	//Don't forget to add respective click handler (onClick())
	const string menuTexts[] = {
		"Play",
		"Create a map",
		"add wtv"
	};

	setSize(400, menu_size * 100);

	//title text
	spTextField title = createTextField("D20 Game");
	title->setFontSize(40);
	title->setPosition(getWidth() / 2, 50);
	addChild(title);

	//create menu option textfields
	for (int i = 0; i < menu_size; i++) {
		spTextField textfield = createTextField(menuTexts[i]);
		textfield->setPosition(getWidth() / 2, title->getPosition().y + ((i+1) * 50));
		textfield->addClickListener(CLOSURE(this, &MainMenu::onClick));
		menuItems.push_back(textfield);
		addChild(textfield);
	}
}

void MainMenu::onClick(Event* e) {
	if (e->target->getName() == "Play") {
		cout << "play" << endl;
	}
	else if (e->target->getName() == "Create a map") {
		cout << "Create" << endl;

		getStage()->removeChildren();
		spMapCreator mc = new MapCreator();
		getStage()->addChild(mc);
		getStage()->setSize(mc->getSize());

		//resize window to fit layout
		SDL_SetWindowSize(getStage()->getAssociatedWindow(), getStage()->getWidth(), getStage()->getHeight());
	}
	else if (e->target->getName() == "add wtv") {
		cout << "add" << endl;
	}
}

MainMenu::~MainMenu() {

}

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
