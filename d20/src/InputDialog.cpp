#include "InputDialog.h"
#include "TextButton.h"

InputDialog::InputDialog(string text, string default) {
	setName("Input Dialog");
	_dialog = true;
	setSize(getStage()->getSize());

	spTextField title = new TextField();
	title->setText(text);
	title->setColor(Color::White);
	title->setFontSize(18);
	title->setAnchor(0.5, 0.5);
	title->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
	title->setPosition(getWidth() / 2, 10);
	addChild(title);

	input = new TextField();
	input->setText(default);
	input->setColor(Color::Red);
	input->setFontSize(20);
	input->setAnchor(0.5, 0.5);
	input->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
	input->setPosition(getWidth() / 2, getHeight() / 2);
	addChild(input);

	spInputText _input = new InputText;
	_input->setAllowedSymbols("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_");
	_input->setMaxTextLength(12);
	_input->start(input);
	spTextButton btn = new TextButton("Ok");
	btn->setPosition(getWidth() - btn->getWidth() - 5, getHeight() - btn->getHeight() - 5);
	btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &InputDialog::finish));
	addChild(btn);
}


InputDialog::~InputDialog() {

}

string InputDialog::getText() {
	return input->getText();
}