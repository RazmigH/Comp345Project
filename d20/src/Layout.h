#pragma once

#include "oxygine-framework.h"
using namespace oxygine;

//This class is to be used for putting together components
// to create a window / scene the user will see
class Layout : public Actor {
public:
	Layout();
	~Layout();
protected:
	Vector2 calculateSize();
private:
};
typedef oxygine::intrusive_ptr<Layout>spLayout;