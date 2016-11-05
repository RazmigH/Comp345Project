//! @file 
//! @brief Implementation file for the Fighter class  
//!

#include "Xml.h"

XMLDocument doc;
const char *fileName;
int id = 1;

//! Xml(fName, numElem) -> constructor which takes the Xml file name along with the number of elements each node will have
Xml::Xml(char *fName, const int numElements) {
	fileName = fName;
	this->numElements = numElements;
}

//! createXmml(rootName) -> creates the xml file and adds a root element using the given name
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
	return retCode;
}

//! addToRoot(elemName, tags, attrs) -> adds to the root element a new element using the provided name
//! then adds text content using the tags and attrs parameters
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
	updateNextID();
	return retCode;
}

//! readDataByID(id) -> returns all the params of the element given by the id
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

//! isEmtpy() -> verifies if the Xml document is empty
bool Xml::isEmpty() {
	openFile();
	XMLNode *pRoot = doc.FirstChild();
	saveFile();
	return (pRoot == nullptr) ? true : false;
}

//! findNextID() -> finds the next available id for the xml node
int Xml::findNextID() {
	openFile();
	const char *pID = doc.FirstChildElement()->Attribute("next_id");
	id = atoi(pID);
	saveFile();
	return id;
}

//! updateNextID() -> increases the available next ID by 1
int Xml::updateNextID() {
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
