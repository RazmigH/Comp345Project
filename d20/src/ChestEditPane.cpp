#include "ChestEditPane.h"
#include "ImageResource.h"

ChestEditPane::ChestEditPane(spChest chest) {
	id = new TextField();
	id->setText("Chest");
	TextStyle style;
	style.font = res::resources.getResFont("small");
	style.color = Color::White;
	style.vAlign = TextStyle::VALIGN_MIDDLE;
	style.hAlign = TextStyle::HALIGN_CENTER;
	id->setStyle(style);
	id->setPosition(0, 0);
	setWidth(150);
	id->setWidth(getWidth());
	this->addChild(id);
}

ChestEditPane::~ChestEditPane() {

}

//isnt called, hardcoding for now
void ChestEditPane::setWidth(float width) {
	id->setWidth(width);
	Actor::setWidth(width);
}