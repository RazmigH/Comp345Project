#pragma once

#include "oxygine-framework.h"
#include "MapTile.h"
using namespace oxygine;

DECLARE_SMART(DefaultEditPane, spDefaultEditPane);
class DefaultEditPane : public Actor {
public:
	DefaultEditPane(spMapTile);
	~DefaultEditPane();

	void setStartPoint(Event*);
private: 
	spMapTile tile;
};