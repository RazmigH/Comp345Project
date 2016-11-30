#include "DefaultEditPane.h"
#include "GameResource.h"
#include "CharacterPicker.h"

DefaultEditPane::DefaultEditPane(spTile t, spMap map) : EditPane(t, map) {
	id = new TextField();
	id->setText(tile->isSolid() ? "Solid Tile" : "Basic Tile");
	id->setFont(res::resources.getResFont("font"));
	id->setHAlign(TextStyle::HALIGN_CENTER);
	this->addChild(id);

	removeNPC = new TextButton("Del NPC");
	removeNPC->setAnchor(0.5, 0.5);
	removeNPC->addEventListener(TouchEvent::CLICK, CLOSURE(this, &DefaultEditPane::onRemoveNPC));

	addNPC = new TextButton("Add NPC");
	addNPC->setAnchor(0.5, 0.5);
	addNPC->addEventListener(TouchEvent::CLICK, CLOSURE(this, &DefaultEditPane::onAddNPC));

	doNPCButtons();

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
	map->setEntryPoint(map->getTileLocation(tile));
}

void DefaultEditPane::setEndPoint(Event* e) {
	map->setExitPoint(map->getTileLocation(tile));
}

void DefaultEditPane::onAddNPC(Event* e) {
	spCharacterPicker picker = new CharacterPicker();
	flow::show(picker, [=](Event*) {
		spCharacter character = picker->getCharacter();
		if (character) {
			Vector2 loc = map->getTileLocation(tile);
			character->setLocation(loc.x, loc.y);
			map->addEntity(character);
			doNPCButtons();
		}
	});
}

void DefaultEditPane::onRemoveNPC(Event* e) {
	vector<spEntity> entities = map->getEntities();
	Vector2 loc = map->getTileLocation(tile);

	for (vector<spEntity>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if (loc == (*it)->getLocation()) {
			map->removeEntity(*it);
			doNPCButtons();
			break;
		}
	}
}

void DefaultEditPane::update(const UpdateState& us) {
	id->setPosition(getWidth() / 2, 5);
	id->setFontSize(getWidth() / 10);
	id->setHeight(getWidth() / 10);

	int currentY = id->getY() + id->getHeight() + 40;
	if (addNPC->getParent() == this) {
		addNPC->setPosition(getWidth() / 2, currentY);
		currentY = addNPC->getY() + addNPC->getHeight() + 15;
	}
	if (removeNPC->getParent() == this) {
		removeNPC->setPosition(getWidth() / 2, currentY);
		currentY = removeNPC->getY() + removeNPC->getHeight() + 15;
	}

	setstart->setPosition(getWidth() / 2, currentY);
	currentY = setstart->getY() + setstart->getHeight() + 15;

	setend->setPosition(getWidth() / 2, currentY);
	currentY = setend->getY() + setend->getHeight() + 15;
}

void DefaultEditPane::doNPCButtons() {
	if (!tile->isSolid()) {
		if (getEntity()) {
			if (addNPC->getParent() == this) {
				removeChild(addNPC);
			}
			this->addChild(removeNPC);
		}
		else {
			if (removeNPC->getParent() == this) {
				removeChild(removeNPC);
			}
			this->addChild(addNPC);
		}
	}
}