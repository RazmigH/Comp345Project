#pragma once
#include "Grid.h"
#include "Entity.h"

//contains the functionality of a game map
DECLARE_SMART(Map, spMap);
class Map : public Grid {
public:
	Map(int cols = 20, int rows = 10);
	~Map();
	Vector2 getEntryPoint();
	Vector2 getExitPoint();
	void move(spEntity, int col, int row, timeMS = 300);
	void update(const UpdateState &rs);

	int getId();
	void setId(int);

	int getNextMapId();
	void setNextMapId(int);

	vector<string> findPath(spTile start, spTile end);

	void addEntity(spEntity);
private:
	spColorRectSprite entryHighlight;
	spColorRectSprite exitHighlight;
	int id;
	int nextMapId = 1;

	struct Location {
		int distanceFromTop;
		int distanceFromLeft;
		vector<string> path;
		string status;
	};
	Location exploreInDirection(Location, string, spTile goalTile);
	vector<Vector2> visited;
	
	Vector2 lastSize;
	vector<spEntity> entities;
};