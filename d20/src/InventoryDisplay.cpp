#pragma once
#include "InventoryDisplay.h"
#include "GameResource.h"

InventoryDisplay::InventoryDisplay(spCharacter c) : character(c)
{
	spTextField textfield = new TextField();
	textfield->setPosition(2,2);
	textfield->setHeight(15);
	TextStyle style;
	style.font = res::resources.getResFont("font");
	style.fontSize = 14;
	style.color = Color::Black;
	textfield->setStyle(style);
	textfield->setText("Inventory");

	inventoryGrid = new DynamicGrid(3, 5, new Tile("inventory-slot"));
	inventoryGrid->setPosition(0, textfield->getY() + textfield->getHeight() + 3);
	inventoryGrid->addClickListener(CLOSURE(this, &InventoryDisplay::onInventoryClick));

	spGrid background = new Grid(3, 10);
	background->setTiles(new Tile("stone"));

	addChild(background);
	addChild(inventoryGrid);
	addChild(textfield);

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