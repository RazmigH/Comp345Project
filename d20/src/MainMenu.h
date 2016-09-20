#pragma once

#include "Layout.h"
using namespace std;

class MainMenu : public Layout {
public:
	MainMenu();
	~MainMenu();
private: 
	vector<spTextField> menuItems;
	spTextField createTextField(string);
	void onClick(Event*);
};
typedef oxygine::intrusive_ptr<MainMenu>spMainMenu;