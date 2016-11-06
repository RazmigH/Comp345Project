#pragma once
#include "InventoryDisplay.h"
#include "ImageResource.h"

InventoryDisplay::InventoryDisplay()
{
	//Make a stone background for the character display using tiles.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++)
		{
			spTile temp = new Tile("stone");
			temp->setPosition(j * 32, i * 32);
			addChild(temp);
		}
	}

	//Sets display for an empty inventory
	spTextField textfield = new TextField();
	textfield->setAnchor(0.5, 0.5);
	textfield->setPosition(32, 10);


	TextStyle style;
	style.font = res::resources.getResFont("font");
	style.fontSize = 14;
	style.color = Color::Black;
	style.vAlign = TextStyle::VALIGN_MIDDLE;
	style.hAlign = TextStyle::HALIGN_CENTER;
	textfield->setStyle(style);
	textfield->setText("Inventory");

	addChild(textfield);
	setEmptyInventory();
}

InventoryDisplay::~InventoryDisplay()
{

}

void InventoryDisplay::setEmptyInventory()
{
	//Set all the inventory default tiles.
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			setInventoryDisplaySlot(new Tile("inventory-slot"), j, i);
		}
	}

}

void InventoryDisplay::setInventoryDisplaySlot(spTile tile, int row, int col)
{
	items[row][col] = tile;
	items[row][col]->setPosition((row * 32), (col * 32)+32);
	addChild(items[row][col]);
}
