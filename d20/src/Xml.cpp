#include "stdafx.h"
#include "Xml.h"

XMLDocument doc;
const char *fileName;
int id = 1;

Xml::Xml(char *fName, const int numElements) {
	fileName = fName;
	this->numElements = numElements;
}

int Xml::createXml(const string rootName) {
	if (!isEmpty()) {
		cerr << "Can't create XML: file is not empty!";
		return -1;
	}

	openFile();
	
	XMLElement *pRoot = doc.NewElement(rootName.c_str());
	pRoot->SetAttribute("next_id",1);
	doc.InsertFirstChild(pRoot);
	
	int retCode = saveFile();
	return 0;
}

int Xml::addToRoot(const string name, const string tags[], const string attrs[]) {
	if (isEmpty()) {
		cerr << "Can't add: root element was not created!";
		return -1;
	}

	findNextID();
	openFile();

	XMLNode *pRoot = doc.FirstChild();
	XMLElement *pName = doc.NewElement(name.c_str());
	pName->SetAttribute("id", id);
	pRoot->InsertEndChild(pName);
	XMLElement *tag;
	for (int i = 0; i < numElements; ++i) {
		tag = doc.NewElement(tags[i].c_str());
		tag->SetText(attrs[i].c_str());
		pName->InsertEndChild(tag);
	}
	
	int retCode = saveFile();
	updateCurrentID();
	return retCode;
}

vector<string> Xml::readDataByID(int id) {
	int lastID = findNextID() - 1;
	if (id > lastID || id < 0) {
		throw out_of_range("Cannot find, non-existant ID!");
	}
	
	bool found = false;
	vector<string> results = {};
	openFile();
	XMLNode *pRoot = doc.FirstChild();
	pRoot->FirstChild();
	XMLElement *pElementGroup = pRoot->FirstChildElement();
	const char *pID = pElementGroup->Attribute("id");
	//cout << endl << pID << endl;
	if (atoi(pID) == id) {
		found = true;
	}
	for (int i = 1; i < lastID && found != true; ++i) {
		pElementGroup = pElementGroup->NextSiblingElement();
		pID = pElementGroup->Attribute("id");
		//cout << endl << pID << endl;
		if (atoi(pID) == id) {
			found = true;
		}
	}
	if (!found) {
		throw out_of_range("Cannot find, non-existant ID!");
	}
	XMLElement *element = pElementGroup->FirstChildElement();
	results.push_back(element->GetText());
	for (int i = 1; i < numElements; ++i) {
		element = element->NextSiblingElement();
		//cout << element->GetText() << endl;
		results.push_back(element->GetText());
	}


	return results;
}

bool Xml::isEmpty() {
	openFile();
	XMLNode *pRoot = doc.FirstChild();
	return (pRoot == nullptr) ? true : false;
}

int Xml::findNextID() {
	openFile();
	const char *pID = doc.FirstChildElement()->Attribute("next_id");
	id = atoi(pID);
	return id;
}

int Xml::updateCurrentID() {
	openFile();

	doc.FirstChildElement()->SetAttribute("next_id", ++id);

	int retCode = saveFile();
	return retCode;
}


int Xml::openFile() {
	XMLError eResult = doc.LoadFile(fileName);
	XMLCheckResult(eResult);
}

int Xml::saveFile() {
	XMLError eResult = doc.SaveFile(fileName);
	XMLCheckResult(eResult);
}
