#pragma once
#include "Tile.h"
#include <clock.h>

DECLARE_SMART(Entity, spEntity);
class Entity : public Tile {
public:
	void setLocation(int x, int y);
	Vector2 getLocation() const;
	void setMoving(long ms);
	bool isMoving();
	void doUpdate(const UpdateState&);

	bool operator==(const Entity&) const;
	bool operator!=(const Entity&) const;
protected:
	Entity();
private:
	Vector2 pos;
	bool moving;
	clock_t start;
	long movingFor;
};