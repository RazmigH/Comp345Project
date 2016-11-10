#pragma once

#include "Layout.h"
using namespace std;

//This class is for the Main Menu window / layout
DECLARE_SMART(MainMenu, spMainMenu);
class MainMenu : public Layout {
public:
	MainMenu();
	~MainMenu();

	void init();
private:
	const int menu_size = 3; //! Amount of menu options
	vector<spTextField> menuItems;
	spTextField createTextField(string);
	void onClick(Event*);
	spTextField title;
};