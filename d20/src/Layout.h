#pragma once

#include "oxygine-framework.h"
#include "oxygine-flow.h"
using namespace oxygine;

//This class is to be used for putting together components
// to create a window / scene the user will see

DECLARE_SMART(Layout, spLayout);
class Layout : public flow::Scene {
public:
	Layout();
	~Layout();

	Vector2 getSize() const;
	float getWidth() const;
	float getHeight() const;
	void setSize(float width, float height);
	void setSize(Vector2);
protected:
	Vector2 calculateSize();
	void fitToWindow(bool useMinSize = false);
	void fitToWindow(Layout*, bool useMinSize = false);
	void addBackButton();
	void addChild(spActor);
	void removeChild(spActor);
private:
	void onBack(Event* e);
	spActor _view;
};