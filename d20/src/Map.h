#pragma once
#include "oxygine-framework.h"
#include "Grid.h"
using namespace oxygine;

//contains the functionality of a game map
class Map : public Grid {
public:
	Map(int = 10, int = 20);
	~Map();
	Vector2 getEntryPoint();
	Vector2 getExitPoint();
	void move(spActor, int, int, timeMS = 200);
	void render(const RenderState &rs);
private:
	spColorRectSprite entryHighlight;
	spColorRectSprite exitHighlight;
};
typedef oxygine::intrusive_ptr<Map>spMap;