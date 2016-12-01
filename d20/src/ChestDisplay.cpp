#include "ChestDisplay.h"
#include "GameResource.h"

ChestDisplay::ChestDisplay(spChest chest) {
	setName("Chest Display");
	this->chest = chest;

	okbtn = new TextButton("Ok");
	okbtn->addEventListener(TouchEvent::CLICK, [=](Event*) {
		finish();
	});

	title = new TextField();
	title->setText("Chest");
	title->setFont(res::resources.getResFont("font"));
	title->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);

	highlight = new ColorRectSprite();
	highlight->setColor(Color::Lime);
	highlight->setAlpha(30000);

	spTile empty = new Tile("inventory-slot");
	grid = new DynamicGrid(15, 10, empty);
	grid->addClickListener(CLOSURE(this, &ChestDisplay::onSelectItem));

	//initialize the tiles
	highlights.resize(grid->getCols());
	for (int i = 0; i < grid->getCols(); ++i) {
		highlights.at(i).resize(grid->getRows());
	}

	for (int col = 0; col < grid->getCols(); col++) {
		for (int row = 0; row < grid->getRows(); row++) {
			highlights[col][row] = highlight->clone();
		}
	}

	addChild(title);
	addChild(okbtn);
	addChild(grid);
	init();
}

void ChestDisplay::init() {
	refreshItems();
}

ChestDisplay::~ChestDisplay() {

}

void ChestDisplay::onSelectItem(Event* e) {
	spTile tile = grid->getTile(e);
	spItem item = dynamic_cast<Item*>(&(*tile));
	if (item) {
		Vector2 loc = grid->getTileLocation(tile);

		if (isSelected(item) == true) {
			removeSelected(item);
			if (highlights[loc.x][loc.y]->getParent() == (spActor) grid) {
				grid->removeChild(highlights[loc.x][loc.y]);
			}
		}
		else {
			addSelected(item);
			grid->addChild(highlights[loc.x][loc.y]);
		}
	}
}

bool ChestDisplay::isSelected(spItem item) {
	for (vector<spItem>::iterator it = selected.begin(); it != selected.end(); ++it) {
		if (item->getObjectID() == (*it)->getObjectID()) {
			return true;
		}
	}
}

void ChestDisplay::addSelected(spItem item) {
	selected.push_back(item);
}

void ChestDisplay::removeSelected(spItem item) {
	for (vector<spItem>::iterator it = selected.begin(); it != selected.end(); ++it) {
		if (item->getObjectID() == (*it)->getObjectID()) {
			selected.erase(it);
			break;
		}
	}
}

void ChestDisplay::refreshItems() {
	grid->clear();

	vector<spItem> items = chest->getItems();
	for (vector<spItem>::iterator it = items.begin(); it != items.end(); ++it) {
		grid->add(*it);
	}
	addChild(grid);
}

vector<spItem> ChestDisplay::getItems() {
	return selected;
}

void ChestDisplay::update() {
	Layout::update();
	setSize(getStage()->getSize());

	title->setPosition(getWidth() / 2 - title->getWidth() / 2, 10);
	title->setFontSize(getHeight() / 20);
	title->setHeight(getHeight() / 20);

	okbtn->setPosition(getWidth() - okbtn->getWidth() - 5, getHeight() - okbtn->getHeight() - 5);
	grid->setPosition(getWidth() / 2 - grid->getWidth() / 2, title->getY() + title->getHeight() + 15);
	grid->setWidth(getWidth() / 1.75);
	grid->setHeight(grid->getTileWidth() * grid->getRows());

	for (int col = 0; col < grid->getCols(); col++) {
		for (int row = 0; row < grid->getRows(); row++) {
			spTile correspondingTile = grid->getTile(col, row);
			highlights[col][row]->setPosition(correspondingTile->getPosition());
			highlights[col][row]->setSize(correspondingTile->getSize());
		}
	}
}