#include <iostream>
#include "app.h"
#include "ImageResource.h"

void app_preinit(){
}

void app_init(){
	//load resources
	res::load();
}

void app_update(){

}

void app_destroy(){
	//unload resources
	res::free();
}