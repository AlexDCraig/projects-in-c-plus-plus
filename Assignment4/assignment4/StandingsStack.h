// **** CLASS: STANDINGSTACK
// will be used to maintain an ordered list of the standings
// this a stack because the final winner will be entered last
// and should declared first


#ifndef STANDINGS_STACK
#define STANDINGS_STACK

#include "Creature.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class StandingsStack
{
private:
	class Node
	{
		friend class StandingsStack;
		Creature* character;
		Node* next;
		Node(Creature* c1, Node* next1 = NULL)
		{
			character = c1;
			next = next1;
		}
	};

	Node *top;

public:
	StandingsStack();
	void eraseAll();
	void push(Creature*);
	Creature* pop();
	bool isEmpty();
	void printList();
};

#endif
