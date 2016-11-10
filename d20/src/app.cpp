#include "app.h"
#include "oxygine-flow.h"
#include "GameResource.h"
#include "MainMenu.h"

using namespace std;
using namespace oxygine;

void app_preinit() {
}

void app_init() {
	flow::init();
	res::load();

	spMainMenu menu = new MainMenu;
	flow::show(menu);
}

void app_update(){
	flow::update();
}

void app_destroy(){
	flow::free();
	res::free();
}