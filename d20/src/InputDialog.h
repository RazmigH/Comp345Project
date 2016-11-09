#pragma once
#include "Layout.h"
using namespace std;

DECLARE_SMART(InputDialog, spInputDialog);
class InputDialog : public Layout {
public:
	InputDialog(string text = "Enter value", string default = "");
	~InputDialog();

	void init();
	string getText();
private: 
	spTextField input;
};