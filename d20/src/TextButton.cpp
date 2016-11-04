#include "TextButton.h"
#include "ImageResource.h"

TextButton::TextButton(std::string text) {
	this->setPriority(10);
	this->setResAnim(res::resources.getResAnim("button"));
	this->setSize(88, 30);

	spTextField textfield = new TextField();
	textfield->attachTo(this);

	textfield->setAnchor(0.5, 0.5);
	textfield->setPosition(this->getWidth() / 2, this->getHeight() / 2);

	TextStyle style;
	style.font = res::resources.getResFont("font");
	style.color = Color::Black;
	style.vAlign = TextStyle::VALIGN_MIDDLE;
	style.hAlign = TextStyle::HALIGN_CENTER;
	textfield->setStyle(style);
	textfield->setText(text);
}