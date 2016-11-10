#include "ItemDB.h"
#include "EquipableItem.h"
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

//! default constructor
ItemDB::ItemDB() {

	ItemDB::DataBase = vector<EquipableItem>();
}

////! constructor that takes a vector of DataBase as input to create an ItemDB
////! @param containerDataBase: vector of DataBase to put in the new container
//ItemDB::ItemDB(vector<EquipableItem> items) {
//	ItemDB::DataBase = items;
//}

//! method to get the DataBase of the container
//! @return : return the vector of DataBase contained in the ItemDB
vector<EquipableItem> ItemDB::getDatabase() {
	return DataBase;
}

//! method to add an item to the item container
//! @param anitem : new item to put in the ItemDB
void ItemDB::storeItem(EquipableItem anitem)
{
	DataBase.push_back(anitem);
	cout << anitem.getName() << " has been added!" << endl;
}

//! method to return equipable items in DB
void ItemDB::listItem()
{
	cout << "All of the following Items are stored in the item database" << endl;
	for (int i = 0; i < DataBase.size(); i++)
	{
		DataBase[i].printDetails();
	}

	cout << "\n End of Database" << endl;

}

//void ItemDB::saveItems() {
//	ofstream myfile("test.txt");
//	if (myfile.is_open())
//	{
//		for (int i = 0; i < DataBase.size(); i++)
//		{
//			myfile << DataBase[i].getType() << endl;
//			myfile << DataBase[i].getName() << endl;
//			myfile << DataBase[i].getStat() << endl;
//			myfile << DataBase[i].getBonus() <<"\n" << endl;
//
//
//		}
//
//		myfile.close();
//	}
//	else cout << "Unable to open file";
//
//}
//
//void ItemDB::loadItems() {
//	ifstream myfile("test.txt");
//	if (myfile.is_open())
//	{
//		while (!myfile.eof()) {
//
//			int lineCount = 0;
//
//			for (int i = 0; i < 5; i++)
//			{
//				int type = DataBase[i].getType();
//				string name = DataBase[i].getName();
//				int stat = DataBase[i].getStat();
//				int bonus = DataBase[i].getBonus();
//				
//				switch (type) {
//				
//				}
//				EquipableItem newItem = EquipableItem(Item::Equipable::type, name, Item::ItemStats::stat, bonus);
//
//			}
//		}
//		myfile.close();
//	}
//	else cout << "Unable to open file";
//
//}
