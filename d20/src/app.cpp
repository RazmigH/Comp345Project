#include <iostream>
#include "app.h"
#include "ImageResource.h"
#include "MainMenu.h"
#include "CharacterDao.h"
#include "oxygine-flow.h"
using namespace oxygine;

void app_preinit(){
}

void app_init(){
	flow::init();

	//load resources
	res::load();

	//test
	cout << "******************CharTest()*********************" << endl;

	CharacterDao* dao = new CharacterDao();

	/*
	Character test(Character::Class::FIGHTER, "Derp Test1", 1, 1, 1);
	Character test2(Character::Class::ARCHER, "Derp Test2", 2, 2, 2);
	Character npc1(Character::Class::FIGHTER, "NPC Test1", 3, 4, 4);
	Character npc2(Character::Class::FIGHTER, "NPC Test2", 3, 5, 5);
	npc2.setHostile(true);
	npc2.setTalk("git gud!");

	dao->addCharacter(&test);
	dao->addCharacter(&test2);
	dao->addCharacter(&npc1);
	dao->addCharacter(&npc2);
	*/

	vector<spCharacter> ccs = dao->getCharacters();
	std::cout << "CHARACTER COUNT: " << ccs.size() << std::endl;
	for (std::vector<spCharacter>::iterator it = ccs.begin(); it != ccs.end(); ++it) {
		spCharacter c = *it;
		c->printStats();
	}

		
	cout << endl << "*************************************************" << endl;

	//show main menu
	flow::show(new MainMenu);
	//spMainMenu menu = new MainMenu;
	//getStage()->addChild(menu);
	//getStage()->setSize(menu->getSize());

	//resize window to fit layout
	//SDL_SetWindowSize(getStage()->getAssociatedWindow(), getStage()->getWidth(), getStage()->getHeight());
}

void app_update(){
	flow::update();
}

void app_destroy(){
	//unload resources
	res::free();

	flow::free();
}