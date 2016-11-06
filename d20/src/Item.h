//! @file 
//! @brief Header file for the Item class  
//!
#ifndef Item_h
#define Item_h

#include <string>
#include<vector>
#include "Enhancement.h"
using namespace std;

//! class for the implementation of items wearable by a character
class Item
{
public:
	// Default constructor
	Item();
	// Constructor
	Item(string type, vector<Enhancement> influences);
	// Constructor with name
	Item(string type, vector<Enhancement> influences, string name);
	// method to get the type of the item
	string getType();
	// method to get the name of the item
	string getName();
	// method to get the influences of the item
	vector<Enhancement> getInfluences();
	//method to validate an item
	bool validateItem();

private:
	//	vector<string> helmet {"Intelligence", "Wisdom", "Armor Class", "Strength","Constitution","Charisma","Dexterity","Attack Bonus","Damage Bonus"};

	string type;
	string name;
	vector<Enhancement> influence;
	vector<string> helmet {"Intelligence", "Wisdom", "Armor Class"};
	vector<string> armor {"Armor Class"};
	vector<string> shield {"Armor Class"};
	vector<string> ring { "Wisdom", "Armor Class", "Strength","Constitution","Charisma"};
	vector<string> belt {"Strength","Constitution"};
	vector<string> boots {"Armor Class","Dexterity"};
	vector<string> weapon { "Attack Bonus","Damage Bonus" };
	int count = 0;


};
#endif

