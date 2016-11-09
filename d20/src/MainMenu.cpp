#include <iostream>
#include "MainMenu.h"
#include "MapPicker.h"
#include "CharacterPicker.h"
#include "Play.h"

MainMenu::MainMenu() {
	setName("Main Menu");

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
		//create textfield
		spTextField textfield = createTextField(menuTexts[i]);
		textfield->setPosition(getWidth() / 2, title->getPosition().y + ((i+1) * 50));
		textfield->addClickListener(CLOSURE(this, &MainMenu::onClick));
		menuItems.push_back(textfield);
		addChild(textfield);
	}

	fitToWindow(this);
}

void MainMenu::onClick(Event* e) {
	if (e->target->getName() == "Play") {
		cout << "play" << endl;

		show(new CharacterPicker, [=](Event*) {
			MainMenu* temp = new MainMenu;
			Vector2 size = temp->getSize();
			SDL_SetWindowSize(getStage()->getAssociatedWindow(), size.x, size.y);
			delete(temp);
		});
		//resize window to fit layout
		//SDL_SetWindowSize(getStage()->getAssociatedWindow(), getStage()->getWidth(), getStage()->getHeight());
	}
	else if (e->target->getName() == "Create a map") {
		cout << "Create" << endl;

		show(new MapPicker, [=](Event*) {
			MainMenu* temp = new MainMenu;
			Vector2 size = temp->getSize();
			SDL_SetWindowSize(getStage()->getAssociatedWindow(), size.x, size.y);
			delete(temp);
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
