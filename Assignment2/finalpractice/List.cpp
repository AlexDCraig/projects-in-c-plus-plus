/*
********************************************************************
*
*
Program Filename: List.cpp
*
*
Author: Alex Hoffer
*
*
** Date: 10/18/2015
** Description: Implements the List class. Adds/removes Item objects,
resizes at user request if full.
** Input: The size of the array of Item objects and the Item objects 
themselves.
** Output: Manipulates its list and prints.
*
********************************************************************/

#include "List.hpp"
#include <string>
#include <iostream>
using namespace std;

List::List()
{
	tracker = 0;
	size = 0;
	products = NULL;
	duplicateElement = 0;
}

List::~List()
{
	delete[] products;
}

/*
********************************************************************
*
Function: List(int size)
** Description: Establishes the member data according to user input.
** Parameters: Size, to establish how many elements the array should hold.

********************************************************************/

List::List(int size)
{
	tracker = 0; // tracker will be used to tell the array which element it should add to
	this->size = size; 
	products = new Item[size]; // products now holds an array of size "size" of Items

	for (int k = 0; k < size; k++)
		products[k] = Item(); // initialize each Item to its default info ("", "", 0, 0)
}

/*
********************************************************************
*
Function: List(List &obj)
** Description: Copy constructor. 
** Parameters: The List object to be initialized to.
** Pre-Conditions: List object on the left must be uninitialized. 
List object on the right must be initialized.
** Post-Conditions: The List object on the left now contains all 
of the information of the right but its pointers are fresh
so manipulating one object won't hurt the other.
*
********************************************************************/

List::List(List &obj)
{
	size = obj.size;
	tracker = obj.tracker;

	products = new Item[size];

	for (int k = 0; k < size; k++)
		products[k] = obj.products[k];
}

/*
********************************************************************
*
Function: operator=(List &refList)
** Description: overloaded = operator
** Parameters: a pre-initialized List object on the right side of 
the = sign
** Pre-Conditions: List object on the left must be already initialized.
** Post-Conditions: left object holds right object's information, just
with different pointers.
*
********************************************************************/

void List::operator=(List &refList)
{
	if (tracker > 0)
		delete[] products;

	size = refList.size;
	tracker = refList.tracker;

	products = new Item[size];

	for (int k = 0; k < size; k++)
		products[k] = refList.products[k];
}

/*
********************************************************************
*
Function: operator==(Item &i1)
** Description: overloaded == operator detects if the Item object
on the right side of the equation is located somewhere in the
List.
** Parameters: an Item
** Post-Conditions: returns a bool stating if the Item was found
or not.
*
********************************************************************/

bool List::operator==(Item &i1) // check to see if the list contains the item on the right side of the truth statement
{
	bool same = false;

	for (int k = 0; k < tracker && same == false; k++)
	{
		duplicateElement = k; // duplicateElement steps thru each element, however if
		// the truth statement below is true, then the loop is exited and duplicateElement
		// holds the element which has the same info as the Item in the parameter.

		if (products[k] == i1) // overloaded operator for the Item class checks member data for copy
			same = true;
	}

	return same;

}

/*
********************************************************************
*
Function: addItem(Item &item1)
** Description: Place an Item into the products array, provided the
conditions are adequate. 
** Parameters: Requires an Item object.
** Pre-Conditions: Item object must exist. The List's number of elements
w/r to its size will determine which section of control the function
enters. Additionally, the function will check to see if the object
is already in the products array.
** Post-Conditions: If an Item is not added, a printed statement
claiming such will occur. If an Item is added, the tracker will increase
to indicate the next element is where the array needs to add to next.
*
********************************************************************/

void List::addItem(Item &item1) // pass Item by reference so the pointer can access its true location
{
	bool match = false;

	for (int k = 0; k < size && match == false; k++) // the loop will be terminated if a match is found or else
		// will terminate if size - 1 is reached
	{

		if (products[k] == item1) // Item's overloaded == returns true if both Items contain
			// equivalent name, unit, and unitPrice members. This is because in order for
			// an item to be a duplicate, the item should have the same name, the same
			// unit and unit prices (because these indicate it's being purchased at the
			// same store as before. If they're not being purchased at the same place
			// their total price will be calculated differently and thus the products
			// should not be considered the same.
		{
			match = true;
			duplicateElement = k; // duplicateElement now holds the element which holds the item's information
			cout << "The item has been located in the list. Would you "
				<< "like to add this quantity to the previous one?" << endl;
			cout << "Enter 1 for yes or 0 for no. ";

			int affirm;

			cin >> affirm;

			if (affirm == 1) // if the user wants to add the quantity
			{
				int dupe = duplicateElement; // the List == finds the item and then sets its member duplicateElement
				// to the element which contains the item
				int sampleQuantity = products[dupe].getQuantity();
				products[dupe] += item1; // overloaded += in the Item class adds member quantities

				cout << "The number of " << products[dupe].getUnit() << " of " << products[dupe].getName()
					<< " has increased from " << sampleQuantity << " to "
					<< products[dupe].getQuantity() << "." << endl;
			}

			else
				cout << "The quantity has not been added." << endl;
		}
	} // if a match was found, this is where the function ends.

	if (match == false) // if in the above loop, a match wasn't found
	{
		cout << endl << "NOTE: The item is valid pending an array boundary check. It is not already in the list. " << endl;
		cout << endl;

		if (tracker == size) // if the element to be added to goes beyond the bounds of the array
		{
			cout << endl << "ERROR: The item cannot be added without going out of the bounds of the array." << endl;
			cout << "Would you like to increase the size of the array? Enter 1 for yes, 0 for no." << endl;

			int userInput;
			cin >> userInput;

			if (userInput == 1) // if the user would like to change the array's size
			{
				cout << "What size would you like to make the array? " << endl;
				int newSize;
				cin >> newSize;

				Item* newProd = new Item[newSize]; // dummy dynamic array newProd will grab the products array

				for (int k = 0; k < size; k++)
					newProd[k] = products[k]; // newProd now holds all the elements of products but is larger

				int retainTracker = tracker; // the location of the next element to add to should remain the same
				products = newProd; // overloaded = operator will erase products, will est. new pointer locations
				size = newSize; // tell products it can now hold more objects
				tracker = retainTracker; // the last two lines are to ensure that the member variables accurately
				// reflect the changes made


				cout << "The array is now of size " << size << "." << endl;

				products[tracker] = item1; // add the item to the next empty element, now of a larger array

				cout << products[tracker].getQuantity() << " " << products[tracker].getUnit()
					<< " of " << products[tracker].getName() << " at " << "$" << products[tracker].getUnitPrice()
					<< " added at element " << tracker << "." << endl;

				++tracker; // move forward into the array

			}

			else if (userInput == 0)
				cout << "The array size has remained the same, and the item has not been added." << endl;

			else
				cout << "ERROR: Invalid number." << endl;

		}

		else // if the next free element is valid, stays within the bounds
		{
			products[tracker] = item1; // the next element holds the item

			cout << products[tracker].getQuantity() << " " << products[tracker].getUnit()
				<< " of " << products[tracker].getName() << " at " << "$" << products[tracker].getUnitPrice()
				<< " added at element " << tracker << "." << endl;

			++tracker;
		}
	}

}

/*
********************************************************************
*
Function: removeItem(Item &item1)
** Description: Look for the parameter Item in the products array,
remove it if found, shift each element backwards as a result so
there are no awkward empty elements and a new element can be
placed at the end.
** Parameters: takes an Item by reference
** Pre-Conditions: Item must exist: then, whether the item resides
in the products array or not will determine where control in the function
goes.
** Post-Conditions: If the Item is in the array, the element where it
is stored will be reset to default and each occupied element ahead of 
the erased element will be shifted backwards to accomodate.
*
********************************************************************/

void List::removeItem(Item &item1)
{
	bool match = false; // will be used to detect if the item has been found
	int placement = 0;

	// The loop requires that EACH dimension of the object must match
	// that of the suspected item. This differs from the one that requires
	// that each of the member data EXCEPT quantity be the same.

	for (int k = 0; k < tracker && match != true; k++) // if the right element is found, terminate the loop
	{
		bool name = false;
		bool quantity = false;
		bool unit = false;
		bool unitPrice = false;

		if (products[k].getName() == item1.getName())
			name = true;

		if (products[k].getQuantity() == item1.getQuantity())
			quantity = true;

		if (products[k].getUnit() == item1.getUnit())
			unit = true;

		if (products[k].getUnitPrice() == item1.getUnitPrice())
			unitPrice = true;




		if (name == true && quantity == true && unit == true && unitPrice == true)
		{
			match = true;
			products[k] = Item(); // the element to be reset is re-initialized to default
			placement = k; // hold on to the now-empty element

			cout << endl << "The item at element " << k << " has been reset to default." << endl;
		}
	}

	if (match == true) // if the item has been found, it must be removed.
	{
		// three separate conditions necessary to erase the element and deal with the array properly

		if (placement == (size - 1)) // Condition 1: No shifting backwards. IF: the element to be erased is the last element
			// in the array. Because placement + 1 would cause the element to be added out of bounds.
		{
			products[placement] = Item();
			cout << "The final element of the array, " << placement
				<< ", is still available since the erased element was the final element in the array." << endl;
			--tracker; // move the tracker back because the previous element can now be added to
		}

		else if (placement == (size - 2)) // Condition 2: When counter reaches size, it MUST not mention the location (placement + 1)
			// because that position is beyond the bounds. IF: the element to be erased is one below the last occupied element.

		{
			for (int counter = placement + 1; placement < size; counter = (placement) % (size - 1))
			{
				if (counter == 0)
				{
					products[placement] = Item(); // at this point, placement indicates the last element because
					// placement % (size - 1) == 0
					cout << "The final element of the array, " << placement
						<< ", is available as a result of pushing elements backwards after the erase." << endl;
					--tracker;
					break;
				}

				products[placement] = products[placement + 1]; // make the freshly empty element equal the one above it
				++placement;
			}
		}


		else // Condition 3: when counter hits size, the final occupied element must be moved backward
			// and therefore placement + 1 must be set to default. IF: The above two cases do not apply.
		{
			for (int counter = placement + 1; placement < size; counter = (counter + 1) % (size - 1))
			{
				if (counter == 0) // if counter reaches the final element
				{
					products[placement] = products[placement + 1]; // push the above element's info into the element below it
					products[placement + 1] = Item(); // make the last element available
					cout << "The final element of the array, " << placement + 1;
					cout << ", is available as a result of pushing elements backwards after the erase." << endl;
					--tracker;
					break;
				}

				products[placement] = products[counter];
				++placement;

			}
		}
	}

	else if (match == false)
		cout << "The item could not be found." << endl;
}

/*
********************************************************************
*
Function: print()
** Description: Uses Item's print member function to see what Items are 
in the List. If an element is empty, it will tell the user.
** Pre-Conditions: This function makes no sense if size = 0 (i.e. if 
the List object is still stuck with default). 
** Post-Conditions: This function will not modify anything, however,
it does perform one operation- it sums up the total prices of 
each Item in the list and reveals the answer.
*
********************************************************************/

void List::print()
{
	cout << endl << "LIST OF ITEMS: " << endl;
	double sum = 0;

	for (int k = 0; k < size; k++)
	{
		if (products[k].getName() == "" && products[k].getQuantity() == 0
			&& products[k].getUnit() == "" && products[k].getUnitPrice() == 0)
		{
			cout << "Empty element exists at element " << k << "." << endl; // to let the user know there is space in the array
		}

		else
		{
			products[k].printReceipt(); // use the Item member function printReceipt() to print off each item
			sum += products[k].getTotalPrice(); // add each Item's total price up
		}
	}

	if (tracker == (size - 1)) // recall: tracker points at the next empty space to be added to
	{
		cout << "That concludes the list. There's a final empty space at element "
			<< tracker << "." << endl;
	}

	else if (tracker == size)
	{
		cout << "That concludes the list. There are no more empty elements." << endl;
	}

	else
	{
		cout << "That concludes the list. The next empty space is at element "
			<< tracker << "." << endl;
	}
	cout << "The total cost of the items on the list is $" << sum << "." << endl;

}
