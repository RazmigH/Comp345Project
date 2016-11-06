#pragma once

#include "oxygine-framework.h"
#include "Chest.h"
using namespace oxygine;

DECLARE_SMART(ChestEditPane, spChestEditPane);
class ChestEditPane : public Actor {
public:
	ChestEditPane(spChest);
	~ChestEditPane();
	void setWidth(float);
private:
	spTextField id;
};