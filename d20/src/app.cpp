#include <iostream>
#include "app.h"
#include "ImageResource.h"
#include "MainMenu.h"

void app_preinit(){
}

void app_init(){
	//load resources
	res::load();

	//show main menu
	spMainMenu menu = new MainMenu;
	getStage()->addChild(menu);
	getStage()->setSize(menu->getSize());

	//resize window to fit layout
	SDL_SetWindowSize(getStage()->getAssociatedWindow(), getStage()->getWidth(), getStage()->getHeight());
}

void app_update(){

}

void app_destroy(){
	//unload resources
	res::free();
}