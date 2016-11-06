//! @file 
//! @brief Implementation file for the Item class  
//!

#include "Item.h"
#include <iostream>

//! default constructor
Item::Item()
{
	type = "";
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type_name, vector<Enhancement> influences)
{
	 //this constructor should verify that an new item of a certain type only 
	// enhances a character statistic valid for this item type
	if (type_name == "Helmet" || type_name == "Armor" || type_name == "Shield" || type_name == "Ring" || type_name == "Belt" || type_name == "Boots" || type_name == "Weapon")
	{
		if (type_name == "Helmet") 
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < helmet.size(); y++) 
				{
					if (influences[i].getType() == helmet[y]) 
					{ 					
						y = helmet.size();
						count += 1;
					}

				}
			}
		}

		if (type_name == "Armor")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < armor.size(); y++)
				{
					if (influences[i].getType() == armor[y]) 
					{
						y = armor.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Shield")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < shield.size(); y++)
				{
					if (influences[i].getType() == shield[y])
					{
						y = shield.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Ring")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < ring.size(); y++)
				{
					if (influences[i].getType() == ring[y]) 
					{
						y = ring.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Belt")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < belt.size(); y++)
				{
					if (influences[i].getType() == belt[y]) 
					{
						y = belt.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Boots")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < boots.size(); y++)
				{
					if (influences[i].getType() == boots[y]) 
					{
						y = boots.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Weapon")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < weapon.size(); y++)
				{
					if (influences[i].getType() == weapon[y]) 
					{
						y = weapon.size();
						count += 1;
					}
				}
			}
		}
		if (count == influences.size())
		{
			type = type_name;
			influence = influences;
			count = 0;
		}
		else
		{
			count = 0;
			cout << "Invalid Item" << endl;
		}
	}
	else {cout << "Invalid Item" << endl;}

}

Item::Item(string type_name, vector<Enhancement> influences, string iName)
{
	//this constructor should verify that an new item of a certain type only 
	// enhances a character statistic valid for this item type
	if (type_name == "Helmet" || type_name == "Armor" || type_name == "Shield" || type_name == "Ring" || type_name == "Belt" || type_name == "Boots" || type_name == "Weapon")
	{
		if (type_name == "Helmet")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < helmet.size(); y++)
				{
					if (influences[i].getType() == helmet[y])
					{
						y = helmet.size();
						count += 1;
					}

				}
			}
		}

		if (type_name == "Armor")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < armor.size(); y++)
				{
					if (influences[i].getType() == armor[y])
					{
						y = armor.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Shield")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < shield.size(); y++)
				{
					if (influences[i].getType() == shield[y])
					{
						y = shield.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Ring")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < ring.size(); y++)
				{
					if (influences[i].getType() == ring[y])
					{
						y = ring.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Belt")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < belt.size(); y++)
				{
					if (influences[i].getType() == belt[y])
					{
						y = belt.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Boots")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < boots.size(); y++)
				{
					if (influences[i].getType() == boots[y])
					{
						y = boots.size();
						count += 1;
					}
				}
			}
		}
		if (type_name == "Weapon")
		{
			for (int i = 0; i < influences.size(); i++)
			{
				string infl = influences[i].getType();

				for (int y = 0; y < weapon.size(); y++)
				{
					if (influences[i].getType() == weapon[y])
					{
						y = weapon.size();
						count += 1;
					}
				}
			}
		}
		if (count == influences.size())
		{
			type = type_name;
			influence = influences;
			name = iName;
			count = 0;
		}
		else
		{
			count = 0;
			cout << "Invalid Item" << endl;
		}
	}
	else { cout << "Invalid Item" << endl; }

}
//! method to get the type of the item
//! @return : type of the item
string Item::getType()
{
	return type;
}

//! method to get the name of the item
//! @return : name of the item
string Item::getName()
{
	return name;
}

//! method to get the influences of the item
//! @return : vector containg the list of stats that the item enhances
vector<Enhancement> Item::getInfluences()
{
	return influence;
}

//! method to validate an item, e.g. verify that an new item of a certain type only enhances a character statistic valid for this item type
//! @return : true if the enhancement list is valid according to the rules, false if not
bool Item::validateItem()
{

	string equip = Item::getType();
	
	vector<Enhancement> enh = getInfluences();

	if (equip == "Helmet" || equip == "Armor" || equip == "Shield" || equip == "Ring" || equip == "Belt" || equip == "Boots" || equip == "Weapon")
	{
		if (equip == "Helmet")
		{
			cout << "this is a helmet" << endl;

			for (int i = 0; i < int(enh.size()); i++)
			{
				string infl = enh[i].getType();

				for (int y = 0; y < int(helmet.size()); y++)
				{
					if (enh[i].getType() == helmet[y])
					{
						count += 1;
						y = helmet.size();
					}

				}
			}
		}

		if (equip == "Armor")
		{
			cout << "this is armor" << endl;

			for (int i = 0; i < int(enh.size()); i++)
			{
				string infl = enh[i].getType();

				for (int y = 0; y < int(armor.size()); y++)
				{
					if (enh[i].getType() == armor[y]) 
					{
						count += 1;
						y = armor.size();
					}
				}
			}
		}
		if (equip == "Shield")
		{

			cout << "this is a shield" << endl;

			for (int i = 0; i < int(enh.size()); i++)
			{
				string infl = enh[i].getType();

				for (int y = 0; y < int(shield.size()); y++)
				{
					if (enh[i].getType() == shield[y]) 
					{
						count += 1;
						y = shield.size();
					}
				}
			}
		}
		if (equip == "Ring")
		{

			cout << "this is a ring" << endl;

			for (int i = 0; i < int(enh.size()); i++)
			{
				string infl = enh[i].getType();

				for (int y = 0; y < int(ring.size()); y++)
				{
					if (enh[i].getType() == ring[y]) 
					{
						count += 1;
						y = ring.size();
					}
				}
			}
		}
		if (equip == "Belt")
		{

			cout << "this is a belt" << endl;

			for (int i = 0; i < int(enh.size()); i++)
			{
				string infl = enh[i].getType();

				for (int y = 0; y < int(belt.size()); y++)
				{
					if (enh[i].getType() == belt[y]) 
					{
						count += 1;
						y = belt.size();
					}
				}
			}
		}
		if (equip == "Boots")
		{

			cout << "this is a boot" << endl;

			for (int i = 0; i < int(enh.size()); i++)
			{
				string infl = enh[i].getType();

				for (int y = 0; y < int(boots.size()); y++)
				{
					if (enh[i].getType() == boots[y]) 
					{
						count += 1;
						y = boots.size();
					}
				}
			}
		}
		if (equip == "Weapon")
		{

			cout << "this is a weapon" << endl;

			for (int i = 0; i < int(enh.size()); i++)
			{
				string infl = enh[i].getType();

				for (int y = 0; y < int(weapon.size()); y++)
				{
					if (enh[i].getType() == weapon[y])
					{
						count += 1;
						y = weapon.size();
					}
				}
			}
		}

		if (count == enh.size())
		{
		count = 0;
		return true;
		}
		else
		{

			count = 0;
			return false;
		}
	}
	else 
	{ 
		return false; 
	}
	
}
