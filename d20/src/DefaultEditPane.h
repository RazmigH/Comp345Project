#pragma once

#include "oxygine-framework.h"
#include "Tile.h"
using namespace oxygine;

DECLARE_SMART(DefaultEditPane, spDefaultEditPane);
class DefaultEditPane : public Actor {
public:
	DefaultEditPane(spTile);
	~DefaultEditPane();

	void setStartPoint(Event*);
	void setEndPoint(Event*);
private: 
	spTile tile;
};