#pragma once
#include "stdafx.h"

using namespace std;
using namespace tinyxml2;

class Xml {

public:
	Xml(char* fName, const int numElements);
	int createXml(const string);
	int addToRoot(const string, const string[], const string[]);
	vector<string> readDataByID(int);
	bool isEmpty();  // private
	int findNextID(); //private
	int updateCurrentID(); //private
	int openFile();
	int saveFile();
private:
	int id;
	int numElements;
	XMLDocument doc;
	char *fileName;
};