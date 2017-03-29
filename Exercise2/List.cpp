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

List::List(int size)
{
	tracker = 0;
	this->size = size;
	products = new Item[size];

	for (int k = 0; k < size; k++)
		products[k] = Item(); // initialize each element to its default info
}

List::List(List &obj) // copy constructor
{
	size = obj.size;
	tracker = obj.tracker;

	products = new Item[size];

	for (int k = 0; k < size; k++)
		products[k] = obj.products[k];
}

void List::operator=(List &refList) // overload =
{
	if (tracker > 0)
		delete[] products;

	size = refList.size;
	tracker = refList.tracker;

	products = new Item[size];

	for (int k = 0; k < size; k++)
		products[k] = refList.products[k];
}

bool List::operator==(Item &i1) // check to see if the list contains the item on the right side of the truth statement
{
	bool same = false;

	for (int k = 0; k < tracker && same == false; k++)
	{
		duplicateElement = k;

		if (products[k] == i1) // overloaded operator for the Item class checks member data for copy
			same = true;
	}

	return same;

}

void List::addItem(Item &item1)
{
	bool match = false;

	for (int k = 0; k < size && match == false; k++)
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
			duplicateElement = k;
			cout << "The item has been located in the list. Would you "
				<< "like to add this quantity to the previous one?" << endl;
			cout << "Enter 1 for yes or 0 for no. ";

			int affirm;

			cin >> affirm;

			if (affirm == 1)
			{
				int dupe = duplicateElement; // the List == finds the item and then sets its member duplicateElement
				// to the element which contains the item
				int sampleQuantity = products[dupe].getQuantity();
				products[dupe] += item1; // overloaded += in the Item class adds quantities

				cout << "The number of " << products[dupe].getUnit() << " of " <<  products[dupe].getName()
					<< " has increased from " << sampleQuantity << " to "
					<< products[dupe].getQuantity() << "." << endl;

			}

			else
				cout << "The quantity has not been added." << endl;
		}
	}

	if (match == false)
	{
		cout << endl << "NOTE: The item is valid pending an array boundary check. It is not already in the list. " << endl;

		if (tracker == size) // if the element to be added to goes beyond the bounds of the array
		{
			cout << endl <<  "ERROR: The item cannot be added without going out of the bounds of the array." << endl;
			cout << "Would you like to increase the size of the array? Enter 1 for yes, 0 for no." << endl;

			int userInput;
			cin >> userInput;

			if (userInput == 1)
			{
				cout << "What size would you like to make the array? " << endl;
				int newSize;
				cin >> newSize;

				Item* newProd = new Item[newSize]; // dummy dynamic array newProd will use to edit the products array

				for (int k = 0; k < size; k++)
					newProd[k] = products[k]; // newProd now holds all the elements of products but is larger

				int retainTracker = tracker;
				products = newProd; // overloaded = operator will erase products, will est. new pointer locations
				size = newSize;
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

		else // if the next free element is valid
		{
			products[tracker] = item1;

			cout << products[tracker].getQuantity() << " " << products[tracker].getUnit()
				<< " of " << products[tracker].getName() << " at " << "$" << products[tracker].getUnitPrice()
				<< " added at element " << tracker << "." << endl;

			++tracker;
		}
	}

}
	void List::removeItem(Item &item1)
	{
		bool match = false; // will be used to detect if the item has been found
		int placement = 0;

		// The loop requires that EACH dimension of the object must match
		// that of the suspected item.

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

		if (match == true)
		{
			// three separate conditions necessary to erase the element and deal with the array properly

			if (placement == (size - 1)) // Condition 1: No shifting backwards. IF: the element to be erased is the last element
				// in the array.
			{
				products[placement] = Item();
				cout << "The final element of the array, " << placement
					<< ", is still available since the erased element was the final element in the array." << endl;
				--tracker;
			}

			else if (placement == (size - 2)) // Condition 2: When counter reaches size, it MUST not mention the location (placement + 1)
				// because that position is beyond the bounds. IF: the element to be erased is one below the last occupied element.

			{
				for (int counter = placement + 1; placement < size; counter = (placement) % (size - 1))
				{
					if (counter == 0)
					{
						products[placement] = Item();
						cout << "The final element of the array, " << placement
							<< ", is available as a result of pushing elements backwards after the erase." << endl;
						--tracker;
						break;
					}

					products[placement] = products[placement + 1];
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
						products[placement] = products[placement + 1];
						products[placement + 1] = Item();
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
