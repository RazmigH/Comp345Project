#pragma once

#include "oxygine-framework.h"
#include "Tile.h"
#include "TextButton.h"
#include "EditPane.h"
using namespace oxygine;

DECLARE_SMART(DefaultEditPane, spDefaultEditPane);
class DefaultEditPane : public EditPane {
public:
	DefaultEditPane(spTile, spMap);
	~DefaultEditPane();

	void setStartPoint(Event*);
	void setEndPoint(Event*);
	void onAddNPC(Event*);
	void onRemoveNPC(Event*);
	void update(const UpdateState& us);
private: 
	void doNPCButtons();

	spTextField id;
	spTextButton addNPC;
	spTextButton removeNPC;
	spTextButton setstart;
	spTextButton setend;
};