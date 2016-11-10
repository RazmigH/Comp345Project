#include "MapPicker.h"
#include "MapCreator.h"
#include <iostream>
using namespace std;

MapPicker::MapPicker(){
	setName("Map Picker");

	highlight = new TextField();
	highlight->setText("<");
	highlight->setFontSize(20);
	highlight->setColor(Color::White);

	okbtn = new TextButton("Ok");
	okbtn->addEventListener(TouchEvent::CLICK, [=](Event*) {
		if (map && getNext()) {
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

	setSize(getStage()->getSize());
	highlight->setPosition(-100, -100);

	okbtn->setPosition(getWidth() - okbtn->getWidth() - 5, getHeight() - okbtn->getHeight() - 5);
	dao = new MapDao();
	vector<spMap> maps = dao->getMaps();
	int y = 5;
	for (vector<spMap>::iterator it = maps.begin(); it != maps.end(); ++it) {
		spTextField tf = new TextField();
		spMap temp = *it;
		tf->setName(to_string(temp->getId()));
		tf->setText(temp->getName());
		tf->setFontSize(20);
		tf->setColor(Color::White);
		tf->setAnchor(0.5, 0.5);
		tf->setHAlign(TextStyle::HorizontalAlign::HALIGN_CENTER);
		tf->setPosition(getWidth() / 2, y);
		tf->setWidth(100);
		tf->addClickListener(CLOSURE(this, &MapPicker::onSelect));
		addChild(tf);
		y += 25;
	}

	addChild(okbtn);
	addBackButton();
	addChild(highlight);
}

MapPicker::~MapPicker() {
	delete(dao);
}

void MapPicker::onSelect(Event* e) {
	spActor temp = safeSpCast<Actor>(e->target);
	if (!map || to_string(map->getId()) != temp->getName()) {
		cout << "Name " << temp->getName() << endl;
		map = dao->getMap(temp->getName());
		removeChild(highlight);
		highlight->setPosition(temp->getX() + temp->getWidth() / 2 + 5, temp->getY());
		addChild(highlight);
		cout << "Selected " << map->getName() << endl;
	}
}

spMap MapPicker::getMap() {
	return map;
}