#pragma once
#include "CharacterDisplay.h"

CharacterDisplay::CharacterDisplay() {
	

	//Set And display default equipement
	spTile helm = new Tile("default-helm");
	helm->setPosition(50, 0);
	addChild(helm);

	spTile armor = new Tile("default-armor");
	armor->setPosition(50, 50);
	addChild(armor);

	spTile weapon = new Tile("default-weapon");
	weapon->setPosition(0, 50);
	addChild(weapon);

	spTile shield = new Tile("default-shield");
	shield->setPosition(100, 50);
	addChild(shield);

	spTile ring = new Tile("default-ring");
	ring->setPosition(100, 100);
	addChild(ring);
	
	spTile boots = new Tile("default-boots");
	boots->setPosition(50, 100);
	addChild(boots);

	spTile belt = new Tile("default-belt");
	belt->setPosition(0, 100);
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
;