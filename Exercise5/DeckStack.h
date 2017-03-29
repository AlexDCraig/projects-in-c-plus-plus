#ifndef DECKSTACK_H
#define DECKSTACK_H

#include "Card.h"
#include <string>
using namespace std;

class DeckStack
{
private:
	friend class Deck;
	class Node
	{
		friend class DeckStack;
		friend class Deck;
		Card* c1;
		Node* next;
		Node(Card* c2, Node* next1 = NULL)
		{
			c1 = c2;
			next = next1;
		}
	};

	Node *top;

public:
	DeckStack();
	void eraseAll();
	void push(Card*);
	Card* pop();
	bool isEmpty();
	void print();
};

#endif
