#include "MapDao.h"
using namespace std;

MapDao::MapDao() {
	xml = new Xml("Maps");
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

	const char* id = element->Attribute("id");
	if (id != nullptr && id != "-1")
		map->setId(stoi(id));

	const char* name = element->Attribute("name");
	if (name != nullptr)
		map->setName(name);

	vector<XMLElement*> tileElements = xml->getChildren(element);
	for (vector<XMLElement*>::iterator it = tileElements.begin(); it != tileElements.end(); ++it) {
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

	for (int r = 0; r < map->getRows(); r++) {
		for (int c = 0; c < map->getCols(); c++) {
			spTile tile = map->getTile(c, r);
			XMLElement* tileXml = tile->getXML(xml);
			tileXml->SetAttribute("col", c);
			tileXml->SetAttribute("row", r);
			root->InsertEndChild(tileXml);
		}
	}

	return root;
}