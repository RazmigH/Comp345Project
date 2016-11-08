#include "DefaultEditPane.h"
#include "ImageResource.h"
#include "TextButton.h"
#include <iostream>

DefaultEditPane::DefaultEditPane(spTile t) {
	this->tile = t;
	setWidth(150);

	int currentY = 0;

	spTextField id = new TextField();
	id->setText(tile->isSolid() ? "Solid Tile" : "Basic Tile");
	TextStyle style;
	style.font = res::resources.getResFont("small");
	style.color = Color::White;
	style.vAlign = TextStyle::VALIGN_MIDDLE;
	style.hAlign = TextStyle::HALIGN_CENTER;
	id->setStyle(style);
	id->setPosition(0, 0);
	id->setWidth(getWidth());
	this->addChild(id);
	currentY = id->getY() + id->getHeight() + 40;

	if (!tile->isSolid()) {
		spTextButton addNPC = new TextButton("Add NPC");
		addNPC->setAnchor(0.5, 0.5);
		addNPC->setPosition(getWidth() / 2, currentY);
		this->addChild(addNPC);
		currentY = addNPC->getY() + addNPC->getHeight() + 15;
	}

	spTextButton setstart = new TextButton("Start Pt.");
	setstart->setAnchor(0.5, 0.5);
	setstart->setPosition(getWidth() / 2, currentY);
	setstart->addEventListener(TouchEvent::CLICK, CLOSURE(this, &DefaultEditPane::setStartPoint));
	this->addChild(setstart);
	currentY = setstart->getY() + setstart->getHeight() + 15;

	spTextButton setend = new TextButton("End Pt.");
	setend->setAnchor(0.5, 0.5);
	setend->setPosition(getWidth() / 2, currentY);
	setend->addEventListener(TouchEvent::CLICK, CLOSURE(this, &DefaultEditPane::setEndPoint));
	this->addChild(setend);
	currentY = setend->getY() + setend->getHeight() + 15;
}

DefaultEditPane::~DefaultEditPane() {

}


void DefaultEditPane::setStartPoint(Event* e) {
	std::cout << "Set tile " << tile->getName() << " isEntry to " << !tile->isEntryTile() << std::endl;
	tile->isEntryTile(!tile->isEntryTile());
	//spActor mapActor = this->tile->getParent();
	//spMap map = dynamic_cast<Map*>(mapActor);
}

void DefaultEditPane::setEndPoint(Event* e) {
	std::cout << "Set tile " << tile->getName() << " isFinsh to " << !tile->isFinishTile() << std::endl;
	tile->isFinishTile(!tile->isFinishTile());
	//spActor mapActor = this->tile->getParent();
	//spMap map = dynamic_cast<Map*>(mapActor);
}