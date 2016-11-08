#pragma once
#include "oxygine-framework.h"
#include "Grid.h"
using namespace oxygine;

//contains the functionality of a game map
class Map : public Grid {
public:
	Map(int rows = 10, int cols = 20);
	~Map();
	Vector2 getEntryPoint();
	Vector2 getExitPoint();
	void move(spActor, int, int, timeMS = 200);
	void render(const RenderState &rs);

	int getId();
	void setId(int);
private:
	spColorRectSprite entryHighlight;
	spColorRectSprite exitHighlight;
	int id;
};
typedef oxygine::intrusive_ptr<Map>spMap;