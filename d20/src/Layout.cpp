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

void Layout::update() {
	int w, h;
	SDL_GetWindowSize(getStage()->getAssociatedWindow(), &w, &h);
	getStage()->setSize(w, h);
}