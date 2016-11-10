#include "EquipableItem.h"
#include "Item.h"
#include <vector>

class ItemDB
{
public:

	// Default constructor
	ItemDB();
	// method to get the items of the container
	vector<EquipableItem> getDatabase();
	// method to add an item to the item container
	void storeItem(EquipableItem anitem);
	// method to list the items in the container
	void listItem();
	//// Save all items to file
	//void saveItems();
	//// load items from save file
	//void loadItems();


protected:
	vector<EquipableItem> DataBase;
};

