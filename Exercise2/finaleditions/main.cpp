/*
********************************************************************
*
*
Program Filename: main.cpp
*
*
Author: Alex Hoffer
*
*
** Date: 10/18/2015
** Description: Incorporates Item and List classes. Demonstrates
their functions to the user.
** Input: Takes information from the user to establish Items (which
are used to fill up the products array) and then asks the user to help
the program perform several duties, such as removal, resizing, and 
adding quantities to previously established Items.
** Output: By the end of the program, there exists a List object
that contains n number of Items, where n is determined by a user-based 
process of adding, removing, resizing, etc.
*
********************************************************************/

#include "Lister.hpp"
#include <string>
#include <iostream>
using namespace std;

/*
********************************************************************
*
Function: getUserItem()
** Description: For convenience, establishes the name, unit, quantity
and unitPrice member values of an Item, fills them in according to user
input, and then returns the Item. The Item returned is generally intended
to be added to a List.
** Post-Conditions: Returns a newItem, but the newItem is susceptible
to whatever values the user gave. In theory, the newItem could contain
invalid values for name, unit, etc.
*
********************************************************************/

Item getUserItem()
{
	string name, unit;
	int quantity;
	double unitPrice;

	cout << "Please enter the name of the item." << endl;
	cin >> name;

	cout << "Please enter the units by which the item is measured (i.e. boxes, lbs)." << endl;
	cin >> unit;

	cout << "Please enter how many of this item you intend to buy." << endl;
	cin >> quantity;

	cout << "Please enter how much each unit of this item costs." << endl;
	cin >> unitPrice;

	Item newItem(name, unit, quantity, unitPrice);

	return newItem;
}

/*
********************************************************************
*
Function: main()
** Description: Demonstrates List and Item functions.

********************************************************************/

int main()
{
	cout << "DEMONSTRATION: Prompt the user to create a list of Items." << endl;
	cout << endl << "How many items are on your list?" << endl;

	int listSize;

	cin >> listSize;

	List list1(listSize);

	for (int k = 0; k < listSize; k++)
	{
		Item ite1;
		cout << endl;
		ite1 = getUserItem();
		list1.addItem(ite1);
	}

	list1.print();

	cout << endl <<
		"***DEMONSTRATION: resizing array when it's full." << endl;

	cout << endl;

	cout << "Let's add an item, even though the list is full: " << endl;
	cout << endl;

	Item userItem = getUserItem();

	list1.addItem(userItem);

	cout << endl;

	cout << "Here's what the list looks like now that we've increased the size and added the item: " << endl;

	cout << endl;

	list1.print();

	cout << endl <<
		"***DEMONSTRATION: adding quantity to pre-existing object."
		<< endl;

	cout << endl << "Please look at the current list and enter EXACTLY the product's name, unit, and unit price of an item you would like to add a quantity to." << endl;

	cout << endl;

	list1.print();

	cout << endl;

	Item it6 = getUserItem();

	cout << endl << "PROVIDED THAT THE ITEM INFO YOU ENTERED DIRECTLY MATCHES THAT OF AN EXISTING ITEM'S NAME, UNIT, AND UNIT PRICE... Let's try and add it." << endl;

	cout << endl;

	list1.addItem(it6);

	cout << endl;
	cout << "***DEMONSTRATION: remove elements from the list." << endl;

	cout << "Please observe the list and think about which item you want to get rid of." << endl;

	list1.print();

	cout << endl << "Now please enter verbatim the information of the item." << endl;

	Item removal = getUserItem();

	list1.removeItem(removal);

	cout << endl << "Let's verify that that item has been removed: " << endl;
	list1.print();

	return 0;
}
