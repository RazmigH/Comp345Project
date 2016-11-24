#include "DefaultEditPane.h"
#include "GameResource.h"

DefaultEditPane::DefaultEditPane(spTile t) {
	this->tile = t;

	id = new TextField();
	id->setText(tile->isSolid() ? "Solid Tile" : "Basic Tile");
	id->setFont(res::resources.getResFont("font"));
	id->setHAlign(TextStyle::HALIGN_CENTER);
	this->addChild(id);

	if (!tile->isSolid()) {
		addNPC = new TextButton("Add NPC");
		addNPC->setAnchor(0.5, 0.5);
		this->addChild(addNPC);
	}

	setstart = new TextButton("Start Pt.");
	setstart->setAnchor(0.5, 0.5);
	setstart->addEventListener(TouchEvent::CLICK, CLOSURE(this, &DefaultEditPane::setStartPoint));
	this->addChild(setstart);

	setend = new TextButton("End Pt.");
	setend->setAnchor(0.5, 0.5);
	setend->addEventListener(TouchEvent::CLICK, CLOSURE(this, &DefaultEditPane::setEndPoint));
	this->addChild(setend);
}

DefaultEditPane::~DefaultEditPane() {

}


void DefaultEditPane::setStartPoint(Event* e) {
	tile->isEntryTile(!tile->isEntryTile());
}

void DefaultEditPane::setEndPoint(Event* e) {
	tile->isFinishTile(!tile->isFinishTile());
}

void DefaultEditPane::update(const UpdateState& us) {
	id->setPosition(getWidth() / 2, 5);
	id->setFontSize(getWidth() / 10);
	id->setHeight(getWidth() / 10);

	int currentY = id->getY() + id->getHeight() + 40;
	if (!tile->isSolid()) {
		addNPC->setPosition(getWidth() / 2, currentY);
		currentY = addNPC->getY() + addNPC->getHeight() + 15;
	}

	setstart->setPosition(getWidth() / 2, currentY);
	currentY = setstart->getY() + setstart->getHeight() + 15;

	setend->setPosition(getWidth() / 2, currentY);
	currentY = setend->getY() + setend->getHeight() + 15;
}