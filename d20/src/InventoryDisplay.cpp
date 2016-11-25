#pragma once
#include "InventoryDisplay.h"
#include "GameResource.h"

InventoryDisplay::InventoryDisplay(spCharacter c) : character(c)
{
	title = new TextField();
	title->setFont(res::resources.getResFont("font"));
	title->setHAlign(TextStyle::HALIGN_CENTER);
	title->setText("Inventory");

	inventoryGrid = new DynamicGrid(3, 5, new Tile("inventory-slot"));
	inventoryGrid->addClickListener(CLOSURE(this, &InventoryDisplay::onInventoryClick));
	inventoryGrid->setAnchor(0.5, 0);

	background = new Grid(3, 10);
	background->setTiles(new Tile("stone"));
	background->setPosition(0, 0);
	background->setPriority(-1);

	addChild(title);
	addChild(inventoryGrid);
	addChild(background);

	character->Character::attachObserver(this);
	refresh();
}

InventoryDisplay::~InventoryDisplay()
{
	character->Character::detachObserver(this);
}

void InventoryDisplay::refresh() {
	inventoryGrid->clear();
	vector<spItem> inventory = character->getInventory();
	for (vector<spItem>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
		inventoryGrid->add(*it);
	}
}

void InventoryDisplay::onInventoryClick(Event* e) {
	spTile tile = inventoryGrid->getTile(e);
	if (!inventoryGrid->isEmpty(tile)) {
		Vector2 loc = inventoryGrid->getTileLocation(tile);
		int vectorPos = loc.y * inventoryGrid->getCols() + loc.x;
		//character->equip(character->getInventory().at(vectorPos));
		character->equip(vectorPos);
	}
}

void InventoryDisplay::update(const UpdateState& us) {
	Actor::update(us);

	title->setFontSize(getWidth() / 15);
	title->setHeight(getWidth() / 15);
	title->setPosition(getWidth() / 2, 2);

	inventoryGrid->setWidth(getWidth() / 1.5);
	inventoryGrid->setHeight(inventoryGrid->getTileWidth() * inventoryGrid->getRows());
	inventoryGrid->setPosition(getWidth() / 2, title->getY() + title->getHeight() + 3);

	background->setSize(getSize());
}