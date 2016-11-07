#pragma once
#include "CharacterDisplay.h"
#include "Character.h"

CharacterDisplay::CharacterDisplay() {


	//Make a stone background for the character display using tiles.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++)
		{
			spTile temp = new Tile("stone");
			temp->setPosition(j * 32, i * 32);
			addChild(temp);
		}
	}
	

	//Set And display default equipement
	spTile helm = new Tile("default-helm");
	helm->setPosition(32, 64);
	addChild(helm);

	spTile armor = new Tile("default-armor");
	armor->setPosition(32, 96);
	addChild(armor);

	spTile weapon = new Tile("default-weapon");
	weapon->setPosition(0, 96);
	addChild(weapon);

	spTile shield = new Tile("default-shield");
	shield->setPosition(64, 96);
	addChild(shield);

	spTile ring = new Tile("default-ring");
	ring->setPosition(64, 128);
	addChild(ring);
	
	spTile boots = new Tile("default-boots");
	boots->setPosition(32, 128);
	addChild(boots);

	spTile belt = new Tile("default-belt");
	belt->setPosition(0, 128);
	addChild(belt);
};

CharacterDisplay::~CharacterDisplay() {


}




//Setters for setting the tile
void CharacterDisplay::setHelm(Tile t)
{
	helm = new Tile(t);
}
void CharacterDisplay::setArmor(Tile t)
{
	armor = new Tile(t);
}
void CharacterDisplay::setBoots(Tile t)
{
	boots = new Tile(t);
}
void CharacterDisplay::setWeapon(Tile t)
{
	weapon = new Tile(t);
}
void CharacterDisplay::setShield(Tile t)
{
	shield = new Tile(t);
}
void CharacterDisplay::setRing(Tile t)
{
	ring = new Tile(t);
}
void CharacterDisplay::setBelt(Tile t)
{
	belt = new Tile(t);
}