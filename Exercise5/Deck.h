// Class: Deck. Will be used with the game and player classes to allow for players to swap the cards belonging to the game deck
#ifndef DECK_H
#define DECK_H

#include <string>
#include "Card.h"
#include "DeckStack.h"
using namespace std;


class Deck
{
protected:
	friend class DeckStack;
	DeckStack cardDeck;
	Card* c1[52]; // deck of cards for use, array of card pointers
public:
	Deck();
	void cardShuffle(); // randomize protected card array, push it onto stack
	void assembleDeck(); // put all the necessary cards in. like a def const
	Card* getNext(); // pop off a card from the stack
	void print();
};
#endif
