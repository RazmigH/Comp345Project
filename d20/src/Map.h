#pragma once
#include "Grid.h"

//contains the functionality of a game map
DECLARE_SMART(Map, spMap);
class Map : public Grid {
public:
	Map(int cols = 20, int rows = 10);
	~Map();
	Vector2 getEntryPoint();
	Vector2 getExitPoint();
	void move(spActor, int col, int row, timeMS = 300);
	void render(const RenderState &rs);

	int getId();
	void setId(int);
private:
	spColorRectSprite entryHighlight;
	spColorRectSprite exitHighlight;
	int id;
};