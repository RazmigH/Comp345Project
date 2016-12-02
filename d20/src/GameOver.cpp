#include "GameOver.h"
#include "GameResource.h"
#include "MainMenu.h"
GameOver::GameOver() {


	gameOver = new TextField();
	gameOver->setFont(res::resources.getResFont("font"));
	gameOver->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
	gameOver->setAnchor(0.5, 0.5);
	gameOver->setText("GAME OVER");

	okbtn = new TextButton("Ok");
	okbtn->addEventListener(TouchEvent::CLICK, [=](Event*) {
		spMainMenu menu = new MainMenu();
		flow::show(menu);
	});

	addChild(gameOver);
	addChild(okbtn);
}

GameOver::~GameOver() {

}


void GameOver::update() {
	Layout::update();
	setSize(getStage()->getSize());

	okbtn->setPosition(getWidth() - okbtn->getWidth() - 5, getHeight() - okbtn->getHeight() - 5);

	gameOver->setFontSize(getHeight() / 7);
	gameOver->setHeight(getHeight() / 7);
	gameOver->setPosition(getWidth() / 2, getHeight() / 2 - gameOver->getHeight());
}