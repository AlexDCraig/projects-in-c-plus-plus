/*
********************************************************************
**Program Filename: buttercup.cpp

**Author: Alex Hoffer

**Date: 10/2/2015

**Description: Accepts a number from the user, then proceeds to chop off
every third iteration. Once the final number is reached, the cycle
begins again at the beginning while retaining the same count. One number remains 
after the process is complete, and it is returned to the user.

**Input: a number that denotes how many suitors exist.

**Output: the number corresponding to the position the user should stand in
if he wants to be a successful suitor.

********************************************************************/

#include <vector>
#include <iostream>
#include <string>
using namespace std;

/*
********************************************************************
** Function: createVector

** Description: accepts a number from the user and then establishes 
a vector of ints that correspond to each number leading up to and
including that number.

** Parameters: an int that is supposed to represent the number
of suitors.

** Pre-Conditions: after the int is received, a vector known as
suitorHolder must be established and filled.

** Post-Conditions: returns a vector of ints.
********************************************************************/
vector <int> createVector(int numSuitors)
{
	vector <int> suitorHolder;

	for (int k = 1; k <= numSuitors; k++) // get a vector containing all of the suitor positions
		suitorHolder.push_back(k);

	return suitorHolder;
}

/*
********************************************************************
** Function: locatePosition

** Description: Uses a while loop to erase the element that corresponds
to every third counted number. Contains a few exceptions just in 
case the user enters unqualified values.

** Parameters: a reference to the vector of ints established above
in createVector.

** Pre-Conditions: the function anticipates that the vector it
receives will correspond to the one produced by the function above.
If the vector doesn't, this function might not produce the correct
answer.

** Post-Conditions: the suitorHolder vector is assumed to contain
only one value, and that value is located at its first element 
because the vector erase function pushes values backwards after
erasing an element.
********************************************************************/
int locatePosition(vector <int> &suitorHolder)
{
	if (suitorHolder.size() > 1) // if there are more than one elements in the vector
	{
		while (suitorHolder.size() > 1) // until there remains only one element in the vector
		{
			static int counter = 0; // static so this statement does not reinitialize counter to 0 each iteration
			counter += 2; // the vector begins at position 0 and must move 2 to its right
			counter = counter % suitorHolder.size(); 
			/* counter needs to consider suitorHolder's size
			   while counter is less than suitorHolder's size it will erase the element that corresponds
			   to (0 + counter) b/c x % y where x < y is always just x. 
			   when counter is the same as suitorHolder's size or counter can cleanly
			   divide itself by size the element 0 will be erased b/c x % y 
			   where x = y or x / y = z where z is a whole number is always 0. 
			   counter will always increase by 2 after the while condition is re-checked
			   and when the counter+=2 is larger than size then the counter % size statement
			   will reflect this by returning the remainder of x / y where x > y 
		   */
			
			int eraseSpot = counter; // just renaming counter to make the next step clearer
			
			suitorHolder.erase(suitorHolder.begin() + eraseSpot);
		}

		return suitorHolder.at(0); // returns the final element which has been shifted downward by vector erase
	}

	else if (suitorHolder.size() == 1) // just a few fun error messages
		throw string("ERROR: There is one suitor and thus one right and wrong position to stand in.\n");

	else if (suitorHolder.size() == 0)
		throw string("ERROR: No suitors.\n");
}

int main()
{
	int suitorNum;
	cout << "Please enter the number of suitors in line to marry the princess. " << endl;
	cin  >> suitorNum;
	
	try
	{
		vector <int> suitorList = createVector(suitorNum);
		cout << "The lucky suitor will be standing at position "
			 << locatePosition(suitorList) << "." << endl;
	}
	
	catch (string error)
	{
		cout << error;
	}

	return 0;
}

