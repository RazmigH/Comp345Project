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


	// Title for Equipement
	spTextField title = new TextField();
	TextStyle style;
	title->setPosition(50, 32);

	style.font = res::resources.getResFont("font");
	style.fontSize = 14;
	style.color = Color::Black;
	style.vAlign = TextStyle::VALIGN_MIDDLE;
	style.hAlign = TextStyle::HALIGN_CENTER;
	title->setStyle(style);
	title->setText("Equipement");

	addChild(title);

	//Fighter Object and stats
	Character f(Character::Class::FIGHTER, "Camilo", 1, 1);
	const enum Stats {
		STR = 0, CON, DEX, INT, WIS, CHA
	};
	string stats[] = {"STR: ", 
					  "CON: ", 
		              "DEX: ", 
					  "INT: ", 
		              "WIS: ", 
		              "CHA: " };


	//Set a Style for the stat display text.
	TextStyle statStyle;
	statStyle.font = res::resources.getResFont("font");
	statStyle.fontSize = 14;
	statStyle.color = Color::Black;
	statStyle.vAlign = TextStyle::VALIGN_MIDDLE;
	statStyle.hAlign = TextStyle::HALIGN_CENTER;


	//Textfields to display the stats.
	spTextField strStat = new TextField();
	strStat->setStyle(statStyle);
	strStat->setPosition(32, 192);
	strStat->setText(stats[0] + "10");
	addChild(strStat);

	spTextField conStat = new TextField();
	conStat->setStyle(statStyle);
	conStat->setPosition(32, 208);
	conStat->setText(stats[1] + "10");
	addChild(conStat);
	
	spTextField dexStat = new TextField();
	dexStat->setStyle(statStyle);
	dexStat->setPosition(32, 224);
	dexStat->setText(stats[2] + "10");
	addChild(dexStat);
	
	spTextField intStat = new TextField();
	intStat->setStyle(statStyle);
	intStat->setPosition(32, 240);
	intStat->setText(stats[3] + "10");
	addChild(intStat);
	
	spTextField wisStat = new TextField();
	wisStat->setStyle(statStyle);
	wisStat->setPosition(32, 256);
	wisStat->setText(stats[4] + "10");
	addChild(wisStat);
	
	spTextField charStat = new TextField();
	charStat->setStyle(statStyle);
	charStat->setPosition(32, 272);
	charStat->setText(stats[5] + "10");
	addChild(charStat);
	




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