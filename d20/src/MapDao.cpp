#include "MapDao.h"
using namespace std;

MapDao::MapDao() {
	xml = new Xml("Maps");
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

int MapDao::addMap(spMap map) {
	return xml->addElement(MapToXml(map));
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
	if (id != nullptr)
		map->setId(stoi(id));

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
		cout << "Map id is" << map->getId() << endl;
		root->SetAttribute("id", map->getId());
	}
	root->SetAttribute("cols", map->getCols());
	root->SetAttribute("rows", map->getRows());

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