#include "Layout.h"
#include "TextButton.h"

Layout::Layout() {

}

Layout::~Layout() {

}

//Calculates the minimum size an Actor will have to be
// to be able to fit all of its children
Vector2 Layout::calculateSize() {
	int maxRequiredHeight = 0;
	int maxRequiredWidth = 0;
	
	for (spActor actor = getFirstChild(); actor != NULL; actor = actor->getNextSibling()) {
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

void Layout::setBackButton(spLayout layout) {
	backLayout = layout;

	//create back button
	spTextButton back = new TextButton("back");
	back->setPosition(5, 5);
	back->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Layout::onBack));
	addChild(back);
}

void Layout::onBack(Event* e) {
	getStage()->removeChild(this);
	getStage()->addChild(backLayout);
	getStage()->setSize(backLayout->getSize());

	//resize window to fit layout
	SDL_SetWindowSize(getStage()->getAssociatedWindow(), getStage()->getWidth(), getStage()->getHeight());
}