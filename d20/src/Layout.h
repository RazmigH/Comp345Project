#pragma once

#include "oxygine-framework.h"
using namespace oxygine;

//This class is to be used for putting together components
// to create a window / scene the user will see
DECLARE_SMART(Layout, spLayout);
class Layout : public Actor {
public:
	Layout();
	~Layout();
protected:
	Vector2 calculateSize();
	void setBackButton(spLayout);
private:
	void onBack(Event* e);
	spLayout backLayout;
};