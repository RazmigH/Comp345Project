#pragma once
#include "oxygine-framework.h"

class Observer : oxygine::ObjectBase {
public:
	~Observer();
	virtual void refresh() = 0;
protected:
	Observer();
};