#pragma once

#include "oxygine-framework.h"
#include "Chest.h"
#include "EditPane.h"
using namespace oxygine;

DECLARE_SMART(ChestEditPane, spChestEditPane);
class ChestEditPane : public EditPane {
public:
	ChestEditPane(spChest, spMap);
	~ChestEditPane();
	void update(const UpdateState& us);
private:
	spTextField id;
};