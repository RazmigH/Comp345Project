#pragma once
#include "InventoryDisplay.h"
#include "ImageResource.h"

InventoryDisplay::InventoryDisplay()
{
	//! 3X3 Inventory Grid item.
	inventoryGrid = new Grid(3, 5);

	//Create event listener for when the user clicks on a grid tile.
	//inventoryGrid->addEventListener(TouchEvent::CLICK, CLOSURE(this, &InventoryDisplay::onClickInventorySlot));


	//Make a stone background for the character inventory using tiles.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++)
		{
			spTile temp = new Tile("stone");
			temp->setPosition(j * 32, i * 32);
			inventoryGrid->addChild(temp);
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

	
	addChild(inventoryGrid);
	setEmptyInventory();
	addChild(textfield);
}

InventoryDisplay::~InventoryDisplay()
{

}

void InventoryDisplay::setEmptyInventory()
{
	inventoryGrid->setTiles(new Tile("inventory-slot"));
}

void InventoryDisplay::setInventoryDisplaySlot(spTile tile, int col, int row)
{
	inventoryGrid->setTile(col, row, tile);
}
void InventoryDisplay::onClickInventorySlot(Event* e) {
	//Invoque item's action when clicked.
	// i.e : Item i = getItemAtPosition(row,rol);
	//			  i.OnClickAction();

}

//!Method to be implemented
/*Item InventoryDisplay::getItemInInventoryGrid(int row, int col, int InventoryID) {

}*/
