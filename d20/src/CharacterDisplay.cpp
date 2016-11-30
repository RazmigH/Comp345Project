#pragma once
#include "CharacterDisplay.h"
#include "Character.h"

CharacterDisplay::CharacterDisplay(spCharacter useCharacter)
{
	character = useCharacter;
	character->attachObserver(this);

	title = new TextField();
	title->setText("Equipment");
	title->setFont(res::resources.getResFont("font"));
	title->setHAlign(TextStyle::HALIGN_CENTER);
	addChild(title);

	grid = new Grid(3, 3);
	grid->setAnchor(0.5, 0);
	grid->setTiles(new Tile("transparent"));
	grid->setTile(HELM_SLOT.x, HELM_SLOT.y, new Tile("default-helm"));
	grid->setTile(WEAPON_SLOT.x, WEAPON_SLOT.y, new Tile("default-weapon"));
	grid->setTile(BODY_SLOT.x, BODY_SLOT.y, new Tile("default-armor"));
	grid->setTile(SHIELD_SLOT.x, SHIELD_SLOT.y, new Tile("default-shield"));
	grid->setTile(AMULET_SLOT.x, AMULET_SLOT.y, new Tile("default-belt"));
	grid->setTile(BOOTS_SLOT.x, BOOTS_SLOT.y, new Tile("default-boots"));
	grid->setTile(RING_SLOT.x, RING_SLOT.y, new Tile("default-ring"));
	addChild(grid);

	background = new Grid(4, 10);
	background->setTiles(new Tile("stone"));
	background->setPosition(0, 0);
	background->setPriority(-1);
	addChild(background);


	TextStyle style;
	style.font = res::resources.getResFont("black");

	strText = new TextField();
	strText->setText("STR: ");
	strText->setStyle(style);
	addChild(strText);

	conText = new TextField();
	conText->setText("CON: ");
	conText->setStyle(style);
	addChild(conText);

	dexText = new TextField();
	dexText->setText("DEX: ");
	dexText->setStyle(style);
	addChild(dexText);

	intText = new TextField();
	intText->setText("INT: ");
	intText->setStyle(style);
	addChild(intText);

	wisText = new TextField();
	wisText->setText("WIS: ");
	wisText->setStyle(style);
	addChild(wisText);

	charText = new TextField();
	charText->setText("CHAR: ");
	charText->setStyle(style);
	addChild(charText);

	refresh();
}

CharacterDisplay::~CharacterDisplay() {

}

void CharacterDisplay::refresh() {
	int str = character->getStat(Character::Stats::STR);
	int con = character->getStat(Character::Stats::CON);
	int dex = character->getStat(Character::Stats::DEX);
	int inte = character->getStat(Character::Stats::INT);
	int wis = character->getStat(Character::Stats::WIS);
	int chari = character->getStat(Character::Stats::CHA);


	strText->setText(strText->getText().substr(0, strText->getText().find(" ") + 1) + to_string(str));
	conText->setText(conText->getText().substr(0, conText->getText().find(" ") + 1) + to_string(con));
	dexText->setText(dexText->getText().substr(0, dexText->getText().find(" ") + 1) + to_string(dex));
	intText->setText(intText->getText().substr(0, intText->getText().find(" ") + 1) + to_string(inte));
	wisText->setText(wisText->getText().substr(0, wisText->getText().find(" ") + 1) + to_string(wis));
	charText->setText(charText->getText().substr(0, charText->getText().find(" ") + 1) + to_string(chari));
}

void CharacterDisplay::update(const UpdateState& us) {
	Actor::update(us);
	title->setFontSize(getWidth() / 15);
	title->setHeight(getWidth() / 15);
	title->setPosition(getWidth() / 2, 5);

	grid->setWidth(getWidth() / 1.5);
	grid->setHeight(grid->getTileWidth() * grid->getRows());
	grid->setPosition(getWidth() / 2, title->getY() + title->getHeight() + 3);

	background->setSize(getSize());

	strText->setFontSize(getWidth() / 10);
	strText->setHeight(getWidth() / 10);
	strText->setPosition(getWidth() / 15, grid->getY() + grid->getHeight() + 15);

	conText->setFontSize(getWidth() / 10);
	conText->setHeight(getWidth() / 10);
	conText->setPosition(getWidth() / 15, strText->getY() + strText->getHeight() + 5);

	dexText->setFontSize(getWidth() / 10);
	dexText->setHeight(getWidth() / 10);
	dexText->setPosition(getWidth() / 15, conText->getY() + conText->getHeight() + 5);

	intText->setFontSize(getWidth() / 10);
	intText->setHeight(getWidth() / 10);
	intText->setPosition(getWidth() / 15, dexText->getY() + dexText->getHeight() + 5);

	wisText->setFontSize(getWidth() / 10);
	wisText->setHeight(getWidth() / 10);
	wisText->setPosition(getWidth() / 15, intText->getY() + intText->getHeight() + 5);

	charText->setFontSize(getWidth() / 10);
	charText->setHeight(getWidth() / 10);
	charText->setPosition(getWidth() / 15, wisText->getY() + wisText->getHeight() + 5);
}

Vector2 CharacterDisplay::resolvePosition(spEquipableItem i) {
	switch (i->getType()) {
		case Item::Equipable::ARMOR:
			return BODY_SLOT;
		case Item::Equipable::BELT:
			return AMULET_SLOT;
		case Item::Equipable::BOOTS:
			return BOOTS_SLOT;
		case Item::Equipable::HELMET:
			return HELM_SLOT;
		case Item::Equipable::RING:
			return RING_SLOT;
		case Item::Equipable::SHIELD:
			return SHIELD_SLOT;
		case Item::Equipable::WEAPON:
			return WEAPON_SLOT;
		default:
			return HELM_SLOT;
	}
}