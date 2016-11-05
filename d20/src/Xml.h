#pragma once
#include "tinyxml2.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace tinyxml2;

class Xml {

public:
	Xml(char* fName, const int numElements);
	int createXml(const string);
	int addToRoot(const string, const string[], const string[]);
	vector<string> readDataByID(int);
	//! TODO: change to private
	bool isEmpty();  // private
	int findNextID(); //private
	int updateNextID(); //private
	int openFile();
	int saveFile();
private:
	int id;
	int numElements;
	XMLDocument doc;
	char *fileName;
};