#pragma once
#include "Tile.h"
#include <clock.h>

DECLARE_SMART(Entity, spEntity);
class Entity : public Tile {
public:
	void setLocation(int x, int y);
	Vector2 getLocation();
	void setMoving(long ms);
	bool isMoving();
	void doUpdate(const UpdateState&);
protected:
	Entity();
private:
	Vector2 pos;
	bool moving;
	clock_t start;
	long movingFor;
};