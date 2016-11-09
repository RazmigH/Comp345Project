//! @file 
//! @brief Implementation file for the Fighter class  
//!

#include "Xml.h"

//! Xml(fName, numElem) -> constructor which takes the Xml file name along with the number of elements each node will have
Xml::Xml(string name) {
	fileName = name + ".xml";

	//load File
	if (loadFile() != XML_SUCCESS || isEmpty()) {
		//create if file doesn't exist or it has no root node (empty)
		XMLElement* pRoot = this->NewElement(name.c_str());
		pRoot->SetAttribute("next_id", 1);
		this->InsertFirstChild(pRoot);

		this->saveFile();
	}
}

Xml::~Xml() {
}

//! isEmpty() -> verifies if the Xml document is empty
bool Xml::isEmpty() {
	return (this->FirstChild() == nullptr);
}

XMLElement* Xml::getRoot() {
	return this->FirstChildElement();
}

int Xml::loadFile() {
	XMLError eResult = LoadFile(fileName.c_str());
	XMLCheckResult(eResult);
}

int Xml::saveFile() {
	XMLError eResult = SaveFile(fileName.c_str());
	XMLCheckResult(eResult);
}

XMLElement* Xml::createElement(string name){
	return this->NewElement(name.c_str());
}

//! addElement(element) -> adds to the root element a new element
//! if an element with the same id exists, it will be replaced
//! if the passed element has no id, next_id is used
//! returns the id of the saved element
int Xml::addElement(XMLElement* e) {
	XMLElement* current;

	//if same id already exists, replace the element with e 
	const char *id = e->Attribute("id");
	if (id != nullptr) {
		current = getElement(id);
		if (current != nullptr) {
			getRoot()->DeleteChild(current);
			cout << "replacing " << fileName << " #" << id << endl;
		}
	}
	else {
		e->SetAttribute("id", getNextID());
		updateNextID();
	}

	getRoot()->InsertEndChild(e);
	saveFile();
	return atoi(e->Attribute("id"));
}

//! getElements() -> returns all of the children of the root node
vector<XMLElement*> Xml::getElements() {
	return getChildren(getRoot());
}

vector<XMLElement*> Xml::getChildren(XMLElement* root) {
	vector<XMLElement*> elements;
	XMLElement* ele = root->FirstChildElement();
	while (ele != nullptr) {
		elements.push_back(ele);
		ele = ele->NextSiblingElement();
	}
	return elements;
}

//! getElement(id) -> returns all the element with the provided id
XMLElement* Xml::getElement(string id) {
	vector<XMLElement*> elements = getElements();
	for (vector<XMLElement*>::iterator it = elements.begin(); it != elements.end(); ++it) {
		XMLElement* ele = *it;
		if (ele->Attribute("id") == id) {
			return ele;
		}
	}
	return nullptr;
}

//! getNextID() -> finds the next available id for the xml node
int Xml::getNextID() {
	const char* next = getRoot()->Attribute("next_id");
	return atoi(next);
}

//! updateNextID() -> increases the available next ID by 1
int Xml::updateNextID() {
	getRoot()->SetAttribute("next_id", getNextID()+1);

	int retCode = saveFile();
	return retCode;
}