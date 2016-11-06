//! @file 
//! @brief Header file for the Enhancement class  
//!
#ifndef ItemCreation_h
#define ItemCreation_h
#include <string>
#include<vector>
#include "Enhancement.h"
#include "Item.h"
#include "itemContainer.h"



using namespace std;
// creates an item
Item createItem();
//list items in itemDB
void itemList(vector<Item> list);




#endif