#pragma once

#include "Layout.h"
using namespace std;

//This class is for the Main Menu window / layout
class MainMenu : public Layout {
public:
	MainMenu();
	~MainMenu();

	void init();
private: 
	vector<spTextField> menuItems;
	spTextField createTextField(string);
	void onClick(Event*);
};