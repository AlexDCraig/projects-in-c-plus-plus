/*** Implementation of StandingsStack class.
 * Purpose: Another data structure for use with creatures, specifically 
 * meant to be used with the class Player. Recall: Last in, first out
 */

#include "Creature.h"
#include "StandingsStack.h"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// default constructor
StandingsStack::StandingsStack()
{
	top = NULL;
	//srand(time(0));
}

// standard add function. the creature pushed on top of the stack will be first to be popped off
void StandingsStack::push(Creature* c1)
{
	top = new Node(c1, top);
}

// flawed function designed to erase all contents of the stack
void StandingsStack::eraseAll()
{
	while (isEmpty() == false)
	{
		Creature* c1 =	pop();
		delete c1;
	}
}

// standard remove function. if the stack isn't empty, pop off the last creature* that was added
Creature* StandingsStack::pop()
{
	Node* placeholder;

	if (isEmpty() == true)
	{
		cout << "Nothing in the stack." << endl;
		exit(1);
	}

	else
	{
		Creature* c1 = top->character; // c1 holds top value
		placeholder = top; // ready top's current address for deletion
		top = top->next; // move top forward
		delete placeholder; // delete top's old address
		return c1; // return the old top value
	}
}

// check to see if the stack contains anything
bool StandingsStack::isEmpty()
{
	if (top == NULL) 
		return true;
	
	else
		return false;
}

// print out all members of the stack, specialized for player class
void StandingsStack::printList()
{	
	while (isEmpty() == false)
	{
		Creature* c1 = pop();
		cout << c1->getName() << " the " << c1->getSpecies() << " of the team " << c1->getOwner() << endl;
		cout << "Their statistics: " << endl;
		double kills = c1->getTimesKilled();
		double deaths = c1->getTimesBeenKilled();
		double ratio;
		if (deaths == 0)
			ratio = kills;
		else
			ratio = kills/deaths;
		
		cout << "KILLS: " << kills << " ||||| DEATHS: " << deaths << " |||| RATIO: " << ratio << endl;
	}
}	
