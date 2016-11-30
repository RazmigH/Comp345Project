#include "Map.h"
#include "queue"
#include "SDL_keyboard.h"

Map::Map(int cols, int rows) : Grid(cols, rows) {
	entryHighlight = new ColorRectSprite();
	entryHighlight->setColor(Color::LimeGreen);
	entryHighlight->setAlpha(50000);
	entryHighlight->setName("entryHighlight");
	Actor::addChild(entryHighlight);

	exitHighlight = new ColorRectSprite();
	exitHighlight->setColor(Color::YellowGreen);
	exitHighlight->setAlpha(50000);
	exitHighlight->setName("exitHighlight");
	Actor::addChild(exitHighlight);

	id = -1;
}

Map::~Map() {

}

Vector2 Map::getEntryPoint() {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			spTile tile = tiles[row][col];
			if (tile->isEntryTile()) {
				return Vector2(col, row);
			}
		}
	}
	return Vector2(cols / 2, rows - 1);
}

Vector2 Map::getExitPoint() {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			spTile tile = tiles[row][col];
			if (tile->isFinishTile()) {
				return Vector2(col, row);
			}
		}
	}
	return Vector2(cols / 2, 0);
}

//moves a tile to provided location with a transition lasting "duration" milliseconds
void Map::move(spEntity actor, int col, int row, timeMS duration) {
	//outer bounds check, dont move if attempting to move out of map
	if (row >= rows || row < 0 || col >= cols || col < 0) {
		log::messageln("Cant move '%d' to %dx%d : Out of bounds", actor->getObjectID(), col, row);
	}
	else {
		//new tile we are moving to exists
		spTile tile = tiles[row][col];

		//dont move if tile is solid
		if (tile->isSolid()) {
			log::messageln("Cant move '%d' to %dx%d : Tile is Solid", actor->getObjectID(), col, row);
		}
		else {
			//smooth transition to new tile
			if (actor->getFirstTween() == NULL && !actor->isMoving()) {
					log::messageln("Moving %d to %dx%d", actor->getObjectID(), col, row);

					actor->setMoving(duration);
					actor->setLocation(col, row);
					actor->addTween(Sprite::TweenPosition(tile->getPosition()), duration);
			}
		}
	}
}

void Map::update(const UpdateState &rs) {
	Grid::update(rs);
	entryHighlight->setSize(getTileWidth(), getTileHeight());
	entryHighlight->setPosition(getEntryPoint().x * getTileWidth(), getEntryPoint().y * getTileHeight());
	exitHighlight->setSize(getTileWidth(), getTileHeight());
	exitHighlight->setPosition(getExitPoint().x * getTileWidth(), getExitPoint().y * getTileHeight());
	addChild(entryHighlight);
	addChild(exitHighlight);

	for (vector<spEntity>::iterator it = entities.begin(); it != entities.end(); ++it) {
		(*it)->setSize(getTileWidth(), getTileHeight());
		if(!(*it)->isMoving())
			(*it)->setPosition((*it)->getLocation().x * getTileWidth(), (*it)->getLocation().y * getTileHeight());
	}
}

int Map::getId() {
	return id;
}
void Map::setId(int id) {
	this->id = id;
}

int Map::getNextMapId() {
	return nextMapId;
}
void Map::setNextMapId(int id) {
	nextMapId = id;
}

vector<string> Map::findPath(spTile start, spTile end) {
	Vector2 startPoint = getTileLocation(start);
	Vector2 endPoint = getTileLocation(end);

	queue<Location> q;
	Location location;
	location.distanceFromLeft = startPoint.x;
	location.distanceFromTop = startPoint.y;
	location.status = "Start";
	q.push(location);

	while (q.size() > 0) {
		Location currentLocation = q.front();
		q.pop();

		//string sides[4] = {"North", "East", "South", "West"};
		//for (int i = 0; i < 4; i++) {
		//string side = sides[i];

		Location newLocation = exploreInDirection(currentLocation, "North", end);
		if (newLocation.status == "Goal") {
			return newLocation.path;
		}
		else if (newLocation.status == "Valid") {
			q.push(newLocation);
		}

		newLocation = exploreInDirection(currentLocation, "East", end);
		if (newLocation.status == "Goal") {
			return newLocation.path;
		}
		else if (newLocation.status == "Valid") {
			q.push(newLocation);
		}

		newLocation = exploreInDirection(currentLocation, "South", end);
		if (newLocation.status == "Goal") {
			return newLocation.path;
		}
		else if (newLocation.status == "Valid") {
			q.push(newLocation);
		}

		newLocation = exploreInDirection(currentLocation, "West", end);
		if (newLocation.status == "Goal") {
			return newLocation.path;
		}
		else if (newLocation.status == "Valid") {
			q.push(newLocation);
		}
	}
	//}

	vector<string> empty;
	return empty;
}

Map::Location Map::exploreInDirection(Location currentLocation, string direction, spTile goalTile) {
	//check here if u face problems, deep copy dis shjit
	vector<string> newPath = currentLocation.path;
	newPath.push_back(direction);

	int dft = currentLocation.distanceFromTop;
	int dfl = currentLocation.distanceFromLeft;

	if (direction == "North") {
		dft -= 1;
	}
	else if (direction == "East") {
		dfl += 1;
	}
	else if (direction == "South") {
		dft += 1;
	}
	else if (direction == "West") {
		dfl -= 1;
	}

	Location newLocation;
	newLocation.distanceFromLeft = dfl;
	newLocation.distanceFromTop = dft;
	newLocation.path = newPath;
	newLocation.status = "Unknown";

	bool v = false;
	for (vector<Vector2>::iterator it = visited.begin(); it != visited.end(); ++it) {
		Vector2 visitedPlace = *it;
		if (newLocation.distanceFromLeft == visitedPlace.x && newLocation.distanceFromTop == visitedPlace.y) {
			v = true;
			break;
		}
	}


	if (newLocation.distanceFromLeft < 0 || newLocation.distanceFromLeft >= getCols() ||
		newLocation.distanceFromTop < 0 || newLocation.distanceFromTop >= getRows()) {
		newLocation.status = "Invalid";
	}
	else {
		spTile t = getTile(newLocation.distanceFromLeft, newLocation.distanceFromTop);
		if (newLocation.distanceFromLeft == getTileLocation(goalTile).x && newLocation.distanceFromTop == getTileLocation(goalTile).y) {
			newLocation.status = "Goal";
		}
		else if ((t != NULL && t->isSolid()) || v) {
			newLocation.status = "Blocked";
		}
		else {
			newLocation.status = "Valid";
			visited.push_back(Vector2(newLocation.distanceFromLeft, newLocation.distanceFromTop));
		}
	}
	return newLocation;
}

void Map::addEntity(spEntity entity) {
	entities.push_back(entity);
	entity->setPriority(10000);
	addChild(entity);
}

void Map::removeEntity(spEntity entity) {
	for (vector<spEntity>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if (entity == *it) {
			removeChild(entity);
			entities.erase(it);
			break;
		}
	}
}

vector<spEntity> Map::getEntities() {
	return entities;
}