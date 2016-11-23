#include "MapPicker.h"
#include "MapCreator.h"
#include "GameResource.h"
using namespace std;

MapPicker::MapPicker(){
	setName("Map Picker");

	highlight = new TextField();
	highlight->setText("<");
	highlight->setAnchor(0.5, 0.5);
	highlight->setFont(res::resources.getResFont("font"));

	okbtn = new TextButton("Ok");
	okbtn->addEventListener(TouchEvent::CLICK, [=](Event*) {
		if (mapId != "" && getNext()) {
			getNext()->init();
			flow::show(getNext(), [=](Event*) {
				init();
			});
		}
		else {
			finish();
		}
	});

	init();
}

void MapPicker::init() {
	clear();
	addChild(okbtn);
	addChild(highlight);
	addBackButton();

	mapTexts.clear();

	vector<spMap> maps = res::mapDao->getMaps();

	for (vector<spMap>::iterator it = maps.begin(); it != maps.end(); ++it) {
		spTextField tf = new TextField();
		tf->setName(to_string((*it)->getId()));
		tf->setText((*it)->getName());
		tf->setAnchor(0.5, 0.5);
		tf->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
		tf->addClickListener(CLOSURE(this, &MapPicker::onSelect));
		tf->setFont(res::resources.getResFont("font"));
		addChild(tf);
		mapTexts.push_back(tf);
	}

	selected = nullptr;
}

void MapPicker::update() {
	Layout::update();
	setSize(getStage()->getSize());

	okbtn->setPosition(getWidth() - okbtn->getWidth() - 5, getHeight() - okbtn->getHeight() - 5);

	int x = getWidth() / 2;
	int y = getHeight() / 8;
	for (vector<spTextField>::iterator it = mapTexts.begin(); it != mapTexts.end(); ++it) {
		(*it)->setPosition(x, y);
		(*it)->setFontSize(getHeight() / 10);
		(*it)->setHeight(getHeight() / 10);
		string text = (*it)->getText();
		(*it)->setWidth((strlen(text.c_str()) * (getHeight() / 10)) * 0.5);
		y = (*it)->getY() + (*it)->getHeight() + 15;
	}

	if (selected) {
		highlight->setFontSize(getHeight() / 10);
		highlight->setPosition(selected->getX() + selected->getWidth() / 2 + 5, selected->getY() - (selected->getHeight() / 2));
	}
}

MapPicker::~MapPicker() {

}

void MapPicker::onSelect(Event* e) {
	spActor temp = safeSpCast<Actor>(e->target);
	mapId = temp->getName();
	selected = temp;
}

spMap MapPicker::getMap() {
	spMap map = res::mapDao->getMap(mapId);
	return map;
}

void MapPicker::setMap(spMap m) {
	mapId = m->getId();
}