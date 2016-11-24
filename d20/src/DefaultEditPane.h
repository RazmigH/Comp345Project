#pragma once

#include "oxygine-framework.h"
#include "Tile.h"
#include "TextButton.h"
using namespace oxygine;

DECLARE_SMART(DefaultEditPane, spDefaultEditPane);
class DefaultEditPane : public Actor {
public:
	DefaultEditPane(spTile);
	~DefaultEditPane();

	void setStartPoint(Event*);
	void setEndPoint(Event*);
	void update(const UpdateState& us);
private: 
	spTile tile;

	spTextField id;
	spTextButton addNPC;
	spTextButton setstart;
	spTextButton setend;
};