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

#include "List.hpp"
#include <unistd.h> // used to create pauses
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

	cout << endl << "Please enter the units by which the item is measured (i.e. boxes, lbs)." << endl;
	cin >> unit;

	cout << endl << "Please enter how many of this item you intend to buy." << endl;
	cin >> quantity;

	cout << endl << "Please enter how much each unit of this item costs." << endl;
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
	cout << "**********DEMONSTRATION: PROMPT THE USER TO CREATE A LIST OF ITEMS.**********" << endl;
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

	usleep(2000000); // pause for 2 seconds

	cout << endl <<
		"**********DEMONSTRATION: GIVE THE OPTION TO RESIZE THE LIST ARRAY IF IT IS FULL.**********" << endl;

	cout << endl;

	usleep(1000000);

	cout << "The list you entered looks like: " << endl;

	cout << endl;

	list1.print();
	
	usleep(1000000);

	cout << endl << endl << "Let's add an item, even though the list is full: " << endl;
	cout << endl;

	usleep(1000000);
	cout << endl;

	Item userItem = getUserItem();
	usleep(1000000);

	list1.addItem(userItem);

	cout << endl;

	usleep(1000000); // pause for 1 second

	cout << "Here's what the list looks like now that we've increased the size and added the item: " << endl;

	cout << endl;

	list1.print();

	usleep(1000000);

	cout << endl <<
		"**********DEMONSTRATION: IF AN ITEM IS ADDED THAT ALREADY EXISTS ON THE LIST, THE PROGRAM SHOULD IDENTIFY THAT IT ALREADY EXISTS AND OFFER TO COMBINE THE PREVIOUS QUANTITY WITH THE USER'S NEW QUANTITY.**********"
		<< endl;

	usleep(1000000);

	cout << endl << "Please look at the current list and enter EXACTLY the product's name, unit, and unit price of an item you would like to add a quantity to." << endl;

	cout << endl;

	list1.print();

	cout << endl;

	usleep(1000000);

	cout << endl << "NOTE: The quantity you indicate for this duplicate item does not have to be the same as the quantity you indicated previously." << endl;

	usleep(1000000);

	cout << endl;

	Item it6 = getUserItem();

	usleep(500000);

	cout << endl << "PROVIDED THAT THE ITEM INFO YOU ENTERED DIRECTLY MATCHES THAT OF AN EXISTING ITEM'S NAME, UNIT, AND UNIT PRICE... Let's try and add it." << endl;

	cout << endl;

	list1.addItem(it6);

	cout << endl;
	usleep(1000000);

	cout << endl;

	cout << "**********DEMONSTRATION: SPECIFIC ITEMS SHOULD BE ABLE TO BE REMOVED FROM THE LIST IF THE USER IS ABLE TO PROVIDE ACCURATE INFORMATION ABOUT THEIR DETAILS.**********" << endl;

	cout << endl << "Please observe the list and think about which item you want to get rid of." << endl;

	list1.print();

	usleep(1000000);

	cout << endl << "Now please enter EXACTLY the information of the item." << endl;
	
	usleep(100000);

	Item removal = getUserItem();

	list1.removeItem(removal);

	cout << endl << "Let's verify that that item has been removed: " << endl;
	usleep(1000000);
	list1.print();

	usleep(1000000);

	cout << endl;

	cout << "**********FINAL DEMONSTRATION: SINCE THE LIST CLASS USES DYNAMIC MEMORY, IT HAS A CONVERT CONSTRUCTOR AND AN OVERLOADED = OPERATOR. BOTH SHOULD FUNCTION PROPERLY.**********" << endl;
	cout << endl << "I will now instantiate a new List object to the same information the user provided." << endl;

	List copyList = list1;

	usleep(1000000);

	cout << endl << "This is the information that copyList now holds: " << endl;
	cout << endl;
	copyList.print();
	usleep(1000000);
	cout << endl;

	cout << endl << "If the copy constructor was created correctly, we can remove an element of copyList and it won't impact the user list." << endl;

	cout << endl << "Please remove an Item from the above Lists to be removed from copyList so that we can demonstrate this: " << endl;
	cout << endl;

	cout << endl << "Please make sure to type the information exactly." << endl;
	cout << endl;

	Item newItem = getUserItem();
	copyList.removeItem(newItem);

	cout << endl;
	usleep(1000000);

	cout << endl << "The copyList list has: " << endl;
	copyList.print();

	usleep(1000000);

	cout << endl;
	cout << endl << "The user's list has: " << endl;
	list1.print();

	usleep(1000000);

	cout << endl << "Now, to prove that the overloaded operator works, I will set the user list equal to the copyList." << endl;

	cout << endl;

	list1 = copyList;

	usleep(500000);

	cout << endl << "The user list now looks like: " << endl;
	cout << endl;
	list1.print();

	usleep(500000);

	cout << endl << "And the copyList still looks like: " << endl;
	cout << endl;
	copyList.print();

	cout << endl << "To prove memory was properly allocated, let us remove an Item this time from the user list. Please enter information exactly as it appears. " << endl;

	cout << endl;
	Item anotherNewItem = getUserItem();
	copyList.removeItem(anotherNewItem);

	usleep(1000000);

	cout << endl << endl << "FINALLY, let's see how the contents of copyList and the user list differ: ";
	cout << endl;

	cout << "The user's list: " << endl;
	cout << endl;

	list1.print();
	usleep(500000);

	cout << endl << "And the copyList: " << endl;
	cout << endl;

	copyList.print();
	usleep(1000000);
	
	cout << endl << "Without the use of copy constructors or the overloaded = operator, these two Lists would be pointing to the same information, and removal would cause catastrophic results." << endl;
	return 0;
}
