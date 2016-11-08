#pragma once
#include "tinyxml2.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace tinyxml2;

class Xml : XMLDocument {

public:
	Xml(string fName);
	~Xml();
	XMLElement* Xml::getRoot();
	XMLElement* createElement(string name);
	int addElement(XMLElement*);
	vector<XMLElement*> getElements();
	XMLElement* getElement(string id);
private:
	int loadFile();
	int saveFile();
	bool isEmpty();

	int getNextID();
	int updateNextID();
	string fileName;
};