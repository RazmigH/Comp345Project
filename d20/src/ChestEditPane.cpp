#include "ChestEditPane.h"
#include "GameResource.h"

ChestEditPane::ChestEditPane(spChest chest, spMap map) : EditPane(chest, map) {
	id = new TextField();
	id->setText("Chest");
	id->setFont(res::resources.getResFont("font"));
	id->setHAlign(TextStyle::HALIGN_CENTER);
	this->addChild(id);
}

ChestEditPane::~ChestEditPane() {

}

void ChestEditPane::update(const UpdateState& us) {
	id->setPosition(getWidth() / 2, 5);
	id->setFontSize(getWidth() / 10);
	id->setHeight(getWidth() / 10);
}