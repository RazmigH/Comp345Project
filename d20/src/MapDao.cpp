#include "MapDao.h"
#include "Character.h"
using namespace std;

MapDao::MapDao() {
	load();
	if (xml->getElement("-1") == nullptr) {
		XMLElement* e = xml->createElement("Map");
		e->SetAttribute("id", "-1");
		e->SetAttribute("cols", 10);
		e->SetAttribute("rows", 5);
		e->SetAttribute("name", "default");
		xml->addElement(e);
	}
}

MapDao::~MapDao() {
	//xml = nullptr;
	delete(xml);
}

vector<spMap> MapDao::getMaps() {
	vector<spMap> maps;
	vector<XMLElement*> elements = xml->getElements();
	for (std::vector<XMLElement*>::iterator it = elements.begin(); it != elements.end(); ++it) {
		maps.push_back(XmlToMap(*it));
	}
	return maps;
}

spMap MapDao::getMap(string id) {
	XMLElement* ele = xml->getElement(id);
	if (ele != nullptr) {
		return XmlToMap(ele);
	}
	return nullptr;
}

void MapDao::addMap(spMap map) {
	int id = xml->addElement(MapToXml(map));
	map->setId(id);
}

spMap MapDao::XmlToMap(XMLElement* element) {
	spMap map;
	const char* colsStr = element->Attribute("cols");
	const char* rowsStr = element->Attribute("rows");

	if (colsStr != nullptr && rowsStr != nullptr)
		map = new Map(stoi(colsStr), stoi(rowsStr));
	else
		map = new Map();

	const char* name = element->Attribute("name");
	if (name != nullptr)
		map->setName(name);

	const char* entrycol = element->Attribute("entrycol");
	const char* entryrow = element->Attribute("entryrow");
	if (entrycol != nullptr && entryrow != nullptr)
		map->setEntryPoint(Vector2(stoi(entrycol), stoi(entryrow)));

	const char* exitcol = element->Attribute("exitcol");
	const char* exitrow = element->Attribute("exitrow");
	if (exitcol != nullptr && exitrow != nullptr)
		map->setExitPoint(Vector2(stoi(exitcol), stoi(exitrow)));

	const char* nextMapID = element->Attribute("next");
	if (nextMapID)
		map->setNextMapId(stoi(nextMapID));

	const char* id = element->Attribute("id");
	if (id != nullptr) {
		if (atoi(id) == -1) {
			map->setTiles(new Tile("blank"));
			return map;
		}
		else {
			map->setId(stoi(id));
		}
	}

	vector<XMLElement*> tileElements = xml->getChildren(element);
	int i = 0;
	for (vector<XMLElement*>::iterator it = tileElements.begin(); it != tileElements.end(); ++it) {
		if (strcmp((*it)->Name(), "entities") == 0) {
			vector<XMLElement*> entities = xml->getChildren(*it);
			for (vector<XMLElement*>::iterator b = entities.begin(); b != entities.end(); ++b) {
				spTile tile = Tile::getFromXML(*b);
				spEntity entity = dynamic_cast<Entity*>(&(*tile));
				map->addEntity(entity);
			}
		}
		else {
			XMLElement* tileElement = *it;
			spTile tile = new Tile();
			tile = tile->getFromXML(tileElement);

			const char* colStr = tileElement->Attribute("col");
			const char* rowStr = tileElement->Attribute("row");
			if (colStr != nullptr && rowStr != nullptr)
				map->setTile(stoi(colStr), stoi(rowStr), tile);
			//else ignore (as it is currently) or set at 0,0 ?

			//TODO validate col/row attrs in here or in setTile
		}
	}

	return map;
}

XMLElement* MapDao::MapToXml(spMap map) {
	XMLElement* root = xml->createElement("Map");
	if (map->getId() != -1) {
		root->SetAttribute("id", map->getId());
	}
	root->SetAttribute("cols", map->getCols());
	root->SetAttribute("rows", map->getRows());
	root->SetAttribute("name", map->getName().c_str());
	root->SetAttribute("entrycol", map->getEntryPoint().x);
	root->SetAttribute("entryrow", map->getEntryPoint().y);
	root->SetAttribute("exitcol", map->getExitPoint().x);
	root->SetAttribute("exitrow", map->getExitPoint().y);
	root->SetAttribute("next", map->getNextMapId());

	for (int r = 0; r < map->getRows(); r++) {
		for (int c = 0; c < map->getCols(); c++) {
			spTile tile = map->getTile(c, r);
			XMLElement* tileXml = tile->getXML(xml);
			tileXml->SetAttribute("col", c);
			tileXml->SetAttribute("row", r);
			root->InsertEndChild(tileXml);
		}
	}

	XMLElement* entities = xml->createElement("entities");
	vector<spEntity> ents = map->getEntities();
	for (vector<spEntity>::iterator it = ents.begin(); it != ents.end(); ++it) {
		XMLElement* entity = (*it)->getXML(xml);
		entities->InsertEndChild(entity);
	}
	root->InsertEndChild(entities);

	return root;
}

void MapDao::load() {
	xml = new Xml("Maps");
}