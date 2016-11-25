#include "TextButton.h"
#include "GameResource.h"

TextButton::TextButton(std::string text) {
	setPriority(10);
	setResAnim(res::resources.getResAnim("button"));
	setSize(88, 30);

	spTextField textfield = new TextField();
	textfield->attachTo(this);

	textfield->setAnchor(0.5, 0.5);
	textfield->setPosition(this->getWidth() / 2, this->getHeight() / 2);

	TextStyle style;
	style.font = res::resources.getResFont("black");
	style.fontSize = 24;
	style.vAlign = TextStyle::VALIGN_MIDDLE;
	style.hAlign = TextStyle::HALIGN_CENTER;
	textfield->setStyle(style);
	textfield->setText(text);
}

TextButton::~TextButton() {

}