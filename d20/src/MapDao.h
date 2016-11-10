#pragma once
#include "Map.h"
#include "Xml.h"

using namespace std;

class MapDao {
public:
	MapDao();
	~MapDao();
	vector<spMap> getMaps();
	spMap getMap(string);
	void addMap(spMap c);
private:
	Xml* xml;
	spMap XmlToMap(XMLElement*);
	XMLElement* MapToXml(spMap);
};