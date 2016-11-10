#include "Layout.h"
#include "TextButton.h"
#include "MainMenu.h"

Layout::Layout() {
	setName("Layout");
	_view = new Actor();
	_view->setName("Layout::_view");
	_view->attachTo(_holder);

	flow::TransitionMove::assign(this);
}

Layout::~Layout() {
	//finish();
}

//Calculates the minimum size an Actor will have to be
// to be able to fit all of its children
Vector2 Layout::calculateSize() {
	int maxRequiredHeight = 0;
	int maxRequiredWidth = 0;
	
	for (spActor actor = _view->getFirstChild(); actor != NULL; actor = actor->getNextSibling()) {
		int heightreq = actor->getPosition().y + actor->getHeight();
		if (heightreq > maxRequiredHeight) {
			maxRequiredHeight = heightreq;
		}

		int widthreq = actor->getPosition().x + actor->getWidth();
		if (widthreq > maxRequiredWidth) {
			maxRequiredWidth = widthreq;
		}
	}

	return Vector2(maxRequiredWidth, maxRequiredHeight);
}

void Layout::fitToWindow(bool useMinSize) {
	fitToWindow(this, useMinSize);
}

void Layout::fitToWindow(Layout* layout, bool useMinSize) {
	if (useMinSize)
		layout->setSize(layout->calculateSize());
	getStage()->setSize(layout->getSize());
	SDL_SetWindowSize(getStage()->getAssociatedWindow(), layout->getWidth(), layout->getHeight());
}

void Layout::clear() {
	clear(_view);
}

void Layout::clear(spActor a) {
	vector<spActor> actors;
	for (spActor actor = a->getFirstChild(); actor != NULL; actor = actor->getNextSibling()) {
		actors.push_back(actor);
	}
	for (vector<spActor>::iterator it = actors.begin(); it != actors.end(); ++it) {
		spActor actor = *it;
		a->removeChild(actor);
	}
}

void Layout::addBackButton() {
	spTextButton back = new TextButton("back");
	back->setPosition(5, 5);
	back->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Layout::onBack));
	addChild(back);
}

void Layout::onBack(Event* e) {
	finish();
}

void Layout::addChild(spActor actor) {
	_view->addChild(actor);
}

void Layout::removeChild(spActor actor) {
	_view->removeChild(actor);
}

Vector2 Layout::getSize() const {
	return _view->getSize();
}

float Layout::getWidth() const {
	return getSize().x;
}

float Layout::getHeight() const {
	return getSize().y;
}

void Layout::setSize(float width, float height) {
	setSize(Vector2(width, height));
}

void Layout::setSize(Vector2 size) {
	_view->setSize(size);
	_holder->setSize(size);
}

void Layout::setNext(spLayout layout) {
	leadTo = layout;
}

spLayout Layout::getNext() {
	return leadTo;
}