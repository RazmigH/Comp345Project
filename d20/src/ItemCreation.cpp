
#include "item.h"
#include "itemContainer.h"
#include "Enhancement.h"
#include <iostream>
using namespace std;

Item createItem() {
	//user created items
	//what item do you want to create (helmet, ring, armor, boots... so on)
	//what enhancments do you want to put on it (stength, intelligence, constituions... so on)
	//how strong do you want the enhancement to be? (1-5)
	//add the item to the DB
	int newItem;
	int numEnh;
	int enhAmt;
	int countd;
	int enhCh;
	int enhSt;
	int ans;
	string name = "";
	string	oneC = "";
	string	twoC = "";
	string	threeC = "";
	string	fourC = "";
	string	fiveC = "";

	vector<Enhancement> newEnhancements;
	Enhancement enhH1;
	Enhancement enhH2;
	Enhancement enhH3;


	cout << "Enter the # that correlates to the item you would like to create \n"
		<< "   #1 - Helmet\n"
		<< "   #2 - Armor\n"
		<< "   #3 - Shield\n"
		<< "   #4 - Ring\n"
		<< "   #5 - Belt\n"
		<< "   #6 - Boots\n"
		<< "   #7 - Weapon\n"
		<< endl;

	cin >> newItem;

	while (!cin || newItem < 1 || newItem >7)
	{
		cin.clear();
		cin.ignore();
		cout << "That does not correlate to an item, please try again" << endl;
		cin >> newItem;
	}

	// switch statement to add item enhancements
	switch (newItem)
	{
		//User selected a helmet. Switch statements to add element enhancments
	case 1:
	{
		cout << "How many of the following enhancmenets would you like to put on this helmet? Please choose between 1-3\n"
			<< "   Armor Class\n"
			<< "   Intelligence\n"
			<< "   Wisdom\n"
			<< endl;
		cin >> numEnh;

		while (!cin || numEnh < 1 || numEnh >3)
		{
			cin.clear();
			cin.ignore();
			cout << "That is not in the specified range, please try again" << endl;
			cin >> numEnh;
		}

		countd = numEnh;

		//creating enhancements
		while (countd > 0)
		{

			cout << "What enhancement would you like to add? Please enter the number correlating to your choice \n"
				<< "   #1 - Armor Class " << oneC << "\n"
				<< "   #2 - Intelligence " << twoC << "\n"
				<< "   #3 - Wisdom " << threeC << "\n"
				<< endl;

			cin >> enhCh;

			while (!cin || enhCh < 1 || enhCh >3)
			{
				cin.clear();
				cin.ignore();
				cout << "That is not in the specified range, please try again" << endl;
				cin >> enhCh;
			}

			if (enhCh == 1) {
				if (oneC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			if (enhCh == 2) {
				if (twoC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			if (enhCh == 3) {
				if (threeC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			switch (enhCh)
			{
				//add Armor Class Enhancement
			case 1:
			{
				cout << "How strong would you like your Armor Class enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhH1("Armor Class", enhSt);
				newEnhancements.push_back(enhH1);
				countd -= 1;
				oneC = "Added";
			}
			break;
			//add Intelligence Enahancement
			case 2:
			{
				cout << "How strong would you like your Intelligence enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhH2("Intelligence", enhSt);
				newEnhancements.push_back(enhH2);
				countd -= 1;
				twoC = "Added";
			}
			break;
			//add Wisdom Enhancement
			case 3:
			{
				cout << "How strong would you like your Wisdom enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhH3("Wisdom", enhSt);
				newEnhancements.push_back(enhH3);
				countd -= 1;
				threeC = "Added";
			}
			break;
			}
		}

		cout << "What is the name of your new item?" << endl;
		cin >> name;

		Item Helmet{ "Helmet", newEnhancements, name };

		return Helmet;

		//end of case 1 item select
	}
	break;
	// user selected Armor
	case 2:
	{

		countd = 1;

		//creating enhancements
		while (countd > 0)
		{

			enhCh = 1;

			cout << "How strong would you like your Armor Class enhancement to be? Choose from 1 - 5" << endl;
			cin >> enhSt;

			while (!cin || enhSt < 1 || enhSt >5)
			{
				cin.clear();
				cin.ignore();
				cout << "That is not in the specified range, please try again" << endl;
				cin >> enhSt;
			}

			Enhancement enhA1("Armor Class", enhSt);
			newEnhancements.push_back(enhA1);
			countd -= 1;
			oneC = "Added";

		}

		cout << "What is the name of your new item?" << endl;
		cin >> name;

		Item Armor{ "Armor", newEnhancements, name };

		return Armor;
		//end of case 2 item select
	}
	break;
	// User selected Shield
	case 3:
	{

		countd = 1;

		//creating enhancements
		while (countd > 0)
		{

			enhCh = 1;

			cout << "How strong would you like your Armor Class enhancement for your shield to be? Choose from 1 - 5" << endl;
			cin >> enhSt;

			while (!cin || enhSt < 1 || enhSt >5)
			{
				cin.clear();
				cin.ignore();
				cout << "That is not in the specified range, please try again" << endl;
				cin >> enhSt;
			}

			Enhancement enhS1("Armor Class", enhSt);
			newEnhancements.push_back(enhS1);
			countd -= 1;
			oneC = "Added";

		}

		cout << "What is the name of your new item?" << endl;
		cin >> name;

		Item Shield{ "Shield", newEnhancements, name };

		return Shield;
		//end of case 3 item select
	}
	break;
	// User selected Ring
	case 4:
	{
		cout << "How many of the following enhancmenets would you like to put on this Ring? Please choose between 1-5\n"
			<< "   Armor Class\n"
			<< "   Strength\n"
			<< "   Wisdom\n"
			<< "   Constitution\n"
			<< "   Charisma\n"
			<< endl;
		cin >> numEnh;

		while (!cin || numEnh < 1 || numEnh >5)
		{
			cin.clear();
			cin.ignore();
			cout << "That is not in the specified range, please try again" << endl;
			cin >> numEnh;
		}

		countd = numEnh;

		//creating enhancements
		while (countd > 0)
		{

			cout << "What enhancement would you like to add? Please enter the number correlating to your choice \n"
				<< "   #1 - Armor Class " << oneC << "\n"
				<< "   #2 - Strength " << twoC << "\n"
				<< "   #3 - Wisdom " << threeC << "\n"
				<< "   #4 - Constitution " << fourC << "\n"
				<< "   #5 - Charisma " << fiveC << "\n"
				<< endl;

			cin >> enhCh;

			while (!cin || enhCh < 1 || enhCh >5)
			{
				cin.clear();
				cin.ignore();
				cout << "That is not in the specified range, please try again" << endl;
				cin >> enhCh;
			}

			if (enhCh == 1) {
				if (oneC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			if (enhCh == 2) {
				if (twoC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			if (enhCh == 3) {
				if (threeC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}
			if (enhCh == 4) {
				if (fourC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			if (enhCh == 5) {
				if (fiveC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			switch (enhCh)
			{
				//add Armor Class Enhancement
			case 1:
			{
				cout << "How strong would you like your Armor Class enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhR1("Armor Class", enhSt);
				newEnhancements.push_back(enhR1);
				countd -= 1;
				oneC = "Added";
			}
			break;
			//add Strength Enahancement
			case 2:
			{
				cout << "How strong would you like your Strength enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhR2("Strength", enhSt);
				newEnhancements.push_back(enhR2);
				countd -= 1;
				twoC = "Added";
			}
			break;
			//add Wisdom Enhancement
			case 3:
			{
				cout << "How strong would you like your Wisdom enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhR3("Wisdom", enhSt);
				newEnhancements.push_back(enhR3);
				countd -= 1;
				threeC = "Added";
			}
			break;
			// Add constitution enhancement
			case 4:
			{
				cout << "How strong would you like your Constitution enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhR4("Constitution", enhSt);
				newEnhancements.push_back(enhR4);
				countd -= 1;
				threeC = "Added";
			}
			break;
			// add Charisma enhancement
			case 5:
			{
				cout << "How strong would you like your Charisma enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhR5("Charisma", enhSt);
				newEnhancements.push_back(enhR5);
				countd -= 1;
				threeC = "Added";
			}
			break;
			}
		}

		cout << "What is the name of your new item?" << endl;
		cin >> name;

		Item Ring{ "Ring", newEnhancements, name };

		return Ring;
		//end of case 4 item select
	}
	break;
	//adding a belt 
	case 5:
	{
		cout << "How many of the following enhancmenets would you like to put on this Belt? Please choose between 1-2\n"
			<< "   Strength\n"
			<< "   Constitution\n"
			<< endl;
		cin >> numEnh;

		while (!cin || numEnh < 1 || numEnh >2)
		{
			cin.clear();
			cin.ignore();
			cout << "That is not in the specified range, please try again" << endl;
			cin >> numEnh;
		}

		countd = numEnh;

		//creating enhancements
		while (countd > 0)
		{

			cout << "What enhancement would you like to add? Please enter the number correlating to your choice \n"
				<< "   #1 - Strength " << oneC << "\n"
				<< "   #2 - Constitution " << twoC << "\n"
				<< endl;

			cin >> enhCh;

			while (!cin || enhCh < 1 || enhCh >2)
			{
				cin.clear();
				cin.ignore();
				cout << "That is not in the specified range, please try again" << endl;
				cin >> enhCh;
			}

			if (enhCh == 1) {
				if (oneC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			if (enhCh == 2) {
				if (twoC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			switch (enhCh)
			{
				//add Strength Class Enhancement
			case 1:
			{
				cout << "How strong would you like your Strength enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhBe1("Strength", enhSt);
				newEnhancements.push_back(enhBe1);
				countd -= 1;
				oneC = "Added";
			}
			break;
			//add Constitution Enahancement
			case 2:
			{
				cout << "How strong would you like your Constitution enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhBe2("Strength", enhSt);
				newEnhancements.push_back(enhBe2);
				countd -= 1;
				twoC = "Added";
			}
			break;
			}
		}

		cout << "What is the name of your new item?" << endl;
		cin >> name;

		Item Belt{ "Belt", newEnhancements , name};

		return Belt;
		//end of case 5 item select
	}
	break;
	// adding boots
	case 6:
	{
		cout << "How many of the following enhancmenets would you like to put on these boots? Please choose between 1-2\n"
			<< "   Armor Class\n"
			<< "   Dexterity\n"
			<< endl;
		cin >> numEnh;

		while (!cin || numEnh < 1 || numEnh >2)
		{
			cin.clear();
			cin.ignore();
			cout << "That is not in the specified range, please try again" << endl;
			cin >> numEnh;
		}

		countd = numEnh;

		//creating enhancements
		while (countd > 0)
		{

			cout << "What enhancement would you like to add? Please enter the number correlating to your choice \n"
				<< "   #1 - Armor Class " << oneC << "\n"
				<< "   #2 - Dexterity " << twoC << "\n"
				<< endl;

			cin >> enhCh;

			while (!cin || enhCh < 1 || enhCh >2)
			{
				cin.clear();
				cin.ignore();
				cout << "That is not in the specified range, please try again" << endl;
				cin >> enhCh;
			}

			if (enhCh == 1) {
				if (oneC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			if (enhCh == 2) {
				if (twoC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			switch (enhCh)
			{
				//add Armor Class Enhancement
			case 1:
			{
				cout << "How strong would you like your Armor Class enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhBo1("Armor Class", enhSt);
				newEnhancements.push_back(enhBo1);
				countd -= 1;
				oneC = "Added";
			}
			break;
			//add Dexterity Enahancement
			case 2:
			{
				cout << "How strong would you like your dexterity enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhBo2("Dexterity", enhSt);
				newEnhancements.push_back(enhBo2);
				countd -= 1;
				twoC = "Added";
			}
			break;
			}
		}

		cout << "What is the name of your new item?" << endl;
		cin >> name;

		Item Boots{ "Boots", newEnhancements , name };

		return Boots;
		//end of case 6 item select
	}
	break;
	// adding weapon
	case 7:
	{
		cout << "How many of the following enhancmenets would you like to put on this weapon? Please choose between 1-2\n"
			<< "   Attack Bonus\n"
			<< "   Damage Bonus\n"
			<< endl;
		cin >> numEnh;

		while (!cin || numEnh < 1 || numEnh >2)
		{
			cin.clear();
			cin.ignore();
			cout << "That is not in the specified range, please try again" << endl;
			cin >> numEnh;
		}

		countd = numEnh;

		//creating enhancements
		while (countd > 0)
		{

			cout << "What enhancement would you like to add? Please enter the number correlating to your choice \n"
				<< "   #1 - Attack Bonus " << oneC << "\n"
				<< "   #2 - Damage Bonus " << twoC << "\n"
				<< endl;

			cin >> enhCh;

			while (!cin || enhCh < 1 || enhCh >2)
			{
				cin.clear();
				cin.ignore();
				cout << "That is not in the specified range, please try again" << endl;
				cin >> enhCh;
			}

			if (enhCh == 1) {
				if (oneC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			if (enhCh == 2) {
				if (twoC == "Added")
				{
					cout << "You have already added this enhancement, please choose another" << endl;
					enhCh = 0;
				}
			}

			switch (enhCh)
			{
				//add Attack Bonus Enhancement
			case 1:
			{
				cout << "How strong would you like your Attack Bonus enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhW1("Attack Bonus", enhSt);
				newEnhancements.push_back(enhW1);
				countd -= 1;
				oneC = "Added";
			}
			break;
			//add Damage Bonus Enahancement
			case 2:
			{
				cout << "How strong would you like your Damage Bonus enhancement to be? Choose from 1 - 5" << endl;
				cin >> enhSt;

				while (!cin || enhSt < 1 || enhSt >5)
				{
					cin.clear();
					cin.ignore();
					cout << "That is not in the specified range, please try again" << endl;
					cin >> enhSt;
				}

				Enhancement enhW2("Damage Bonus", enhSt);
				newEnhancements.push_back(enhW2);
				countd -= 1;
				twoC = "Added";
			}
			break;
			}
		}

		cout << "What is the name of your new item?" << endl;
		cin >> name;

		Item Weapon{ "Weapon", newEnhancements , name};

		return Weapon;
		//end of case 7 item select
	}
	break;
	}

}

void itemList(vector<Item> list)
{
	for (int i = 0; i < int(list.size()); i++)
	{
		string a = list[i].getType();
		vector <Enhancement> b = list[i].getInfluences();
		string c = list[i].getName();

		cout << "Item " << i + 1 << ": " << c << endl;
		cout << "   " << list[i].getType() << endl;

		for (int y = 0; y < int(b.size()); y++)
		{
			cout << "     " << b[y].getType() << ": " << b[y].getBonus() << endl;
		}

		cout << endl;
	}

}