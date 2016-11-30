#include "Entity.h"

Entity::Entity() {

}

void Entity::setLocation(int x, int y) {
	setLocation(Vector2(x, y));
}

void Entity::setLocation(Vector2 v) {
	this->pos = v;
}

Vector2 Entity::getLocation() const{
	return pos;
}

void Entity::setMoving(long ms) {
	if (!moving) {
		movingFor = ms;
		start = clock();
		moving = true;
	}
}

void Entity::doUpdate(const UpdateState& us) {
	if (moving) {
		long timePassed = clock() - start;
		long ms = double(timePassed) / CLOCKS_PER_SEC * 1000;
		if (ms >= movingFor) {
			moving = false;
			movingFor = 0;
		}
	}
}

bool Entity::isMoving() {
	return moving;
}

bool Entity::operator==(const Entity& other) const {
	return this->getLocation() == other.getLocation() && Tile::operator==(other);
}

bool Entity::operator!=(const Entity& other) const {
	return !(*this == other);
}