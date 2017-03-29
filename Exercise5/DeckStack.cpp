// Implementation of the DeckStack class.

#include "DeckStack.h"
#include "Card.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

// default constructor
DeckStack::DeckStack()
{
	top = NULL;
}

// standard add function. the card pushed on top of the stack will be first to be popped off
void DeckStack::push(Card* c2)
{
	top = new Node(c2, top);
}

void DeckStack::eraseAll()
{
	while (isEmpty() == false)
	{
		pop();
	}
}

// standard remove function. if the stack isn't empty, pop off the last card* that was added
Card* DeckStack::pop()
{
	Node* placeholder;

	if (isEmpty() == true)
	{
		cout << "Nothing in the stack." << endl;
		exit(1);
	}

	else
	{
		Card* c4 = top->c1; // c1 holds top value
		placeholder = top; // ready top's current address for deletion
		top = top->next; // move top forward
		delete placeholder; // delete top's old address
		return c4; // return the old top value
	}
}

// check to see if the stack contains anything
bool DeckStack::isEmpty()
{
	if (top == NULL) 
		return true;
	
	else
		return false;
}

// print out all members of the stack, specialized for player class
void DeckStack::print()
{	
	Node* place = top;
	Node* next = top->next;

	while (next->next != NULL)
	{
		cout << place->c1->rank << " of " << place->c1->suit << endl;
		place = next;
		next = next->next;
	}
}
