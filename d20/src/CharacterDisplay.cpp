#pragma once
#include "CharacterDisplay.h"
#include "Character.h"

CharacterDisplay::CharacterDisplay(spCharacter useCharacter)
{
	character = useCharacter;
	character->attachObserver(this);
	setEmptyDisplay();
	displayStats();
	
}

CharacterDisplay::~CharacterDisplay() {

}

void CharacterDisplay::setEmptyDisplay() {
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
	helm = new Tile("default-helm");
	helm->setPosition(32, 64);
	addChild(helm);

	armor = new Tile("default-armor");
	armor->setPosition(32, 96);
	addChild(armor);

	weapon = new Tile("default-weapon");
	weapon->setPosition(0, 96);
	addChild(weapon);

	shield = new Tile("default-shield");
	shield->setPosition(64, 96);
	addChild(shield);

	ring = new Tile("default-ring");
	ring->setPosition(64, 128);
	addChild(ring);

	boots = new Tile("default-boots");
	boots->setPosition(32, 128);
	addChild(boots);

	belt = new Tile("default-belt");
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

	//displayStats();

}

void CharacterDisplay::displayStats() {
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
	strStat->setText("STR: " + to_string(character->getStat(Character::Stats::STR)));
	addChild(strStat);

	spTextField conStat = new TextField();
	conStat->setStyle(statStyle);
	conStat->setPosition(32, 208);
	conStat->setText("CON: " + to_string(character->getStat(Character::Stats::CON)));
	addChild(conStat);

	spTextField dexStat = new TextField();
	dexStat->setStyle(statStyle);
	dexStat->setPosition(32, 224);
	dexStat->setText("DEX: " + to_string(character->getStat(Character::Stats::DEX)));
	addChild(dexStat);

	spTextField intStat = new TextField();
	intStat->setStyle(statStyle);
	intStat->setPosition(32, 240);
	intStat->setText("INT: " + to_string(character->getStat(Character::Stats::INT)));
	addChild(intStat);

	spTextField wisStat = new TextField();
	wisStat->setStyle(statStyle);
	wisStat->setPosition(32, 256);
	wisStat->setText("WIS: " + to_string(character->getStat(Character::Stats::WIS)));
	addChild(wisStat);

	spTextField charStat = new TextField();
	charStat->setStyle(statStyle);
	charStat->setPosition(32, 272);
	charStat->setText("CHAR: " + to_string(character->getStat(Character::Stats::CHA)));
	addChild(charStat);
}


//Setters for setting the tile
void CharacterDisplay::setHelm(spTile t)
{
	removeChild(helm);
	helm = t;
	addChild(helm);
}
void CharacterDisplay::setArmor(spTile t)
{
	removeChild(armor);
	armor = t;
	addChild(armor);
}
void CharacterDisplay::setBoots(spTile t)
{
	removeChild(boots);
	boots = t;
	addChild(boots);
}
void CharacterDisplay::setWeapon(spTile t)
{
	removeChild(weapon);
	weapon = t;
	addChild(weapon);
}
void CharacterDisplay::setShield(spTile t)
{
	removeChild(shield);
	shield = t;
	addChild(shield);
}
void CharacterDisplay::setRing(spTile t)
{
	removeChild(ring);
	ring = t;
	addChild(ring);
}
void CharacterDisplay::setBelt(spTile t)
{
	removeChild(belt);
	belt = t;
	addChild(belt);
}

void CharacterDisplay::refresh() {
	/*vector<spItem> items = character->getEquipment();
	for (vector<spItem>::iterator it = items.begin(); it != items.end(); ++it) {
		spItem item = *it;
		string typestr = item->getTypeStr();
		if (typestr == "helmet")
			setHelm(item);
		else if (typestr == "armor")
			setArmor(item);
		else if (typestr == "shield")
			setShield(item);
		else if (typestr == "ring")
			setRing(item);
		else if (typestr == "belt")
			setBelt(item);
		else if (typestr == "boots")
			setBoots(item);
		else if (typestr == "weapon")
			setWeapon(item);
	}*/
}
