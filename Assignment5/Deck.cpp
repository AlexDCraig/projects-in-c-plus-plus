/* Implementation file of the Deck class. */

#include "Deck.h"
#include "DeckStack.h"
#include "Card.h"
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

Deck::Deck()
{
	for (int i = 0; i < 52; i++)
		c1[i] = new Card;	// dynamically allocate 52 cards to serve as the deck
}

void Deck::assembleDeck() // initialize cards to standard set
{
	string suits[4] = { "clubs", "diamonds", "hearts", "spades" };
	string royal[4] = { "ace", "jack", "queen", "king" };	
	string nums[9] = { "2", "3", "4", "5", "6", "7", "8", "9", "10" };

	// assign equal numbers of suits the cards
	for (int j = 0; j < 13; j++) // clubs
	{	
			c1[j]->suit = suits[0];
	}

	for (int j = 13; j < 26; j++) // diamonds
	{
			c1[j]->suit = suits[1];
	}

	for (int j = 26; j < 39; j++) // hearts
	{
			c1[j]->suit = suits[2];
	}

	for (int j = 39; j < 52; j++) // spades
	{
			c1[j]->suit = suits[3];
	}
	
	int counter = 0;
	// assign clover, spade, diamond, heart each to ace, jack, queen, king
	for (int k = 0; k < 4; k++) // assign the special cards to the first four of each suit 
	{
			c1[k]->rank = royal[k]; // for clover
	}

	counter = 0;

	for (int k = 13; k < 17; k++) // first four of that suit
	{
			c1[k]->rank = royal[counter];
			counter++;
	}

	counter = 0;

	for (int k = 26; k < 30; k++)
	{
			c1[k]->rank = royal[counter];
			counter++;
	}

	counter = 0;

	for (int k = 39; k < 43; k++)
	{
			c1[k]->rank = royal[counter];
			counter++;
	}
	
	counter = 0;

	// assign the numbers 2-10 to c, d, h, s after the royals
	for (int m = 4; m < 13; m++)
	{
		c1[m]->rank = nums[counter];
		counter++;
	}	
	
	counter = 0;

	for (int m = 17; m < 26; m++)
	{
		c1[m]->rank = nums[counter];
		counter++;
	}

	counter = 0;	
	
	for (int m = 30; m < 39; m++)
	{
		c1[m]->rank = nums[counter];
		counter++;
	}

	counter = 0;

	for (int m = 43; m < 52; m++)
	{
		c1[m]->rank = nums[counter];
		counter++;
	}

}

// intended to rearrange the deck randomly
void Deck::cardShuffle()
{
	vector <Card*> vec;

	for (int k = 0; k < 52; k++)
		vec.push_back(c1[k]);	
	
	random_shuffle (vec.begin(), vec.end());

	for (int k = 0; k < 52; k ++)
		c1[k] = vec.at(k);

	// pop them onto the stack
	// get the cards into proper form

	for (int k = 0; k < 52; k++)
	{
		cardDeck.push(c1[k]);	
	}			
}	

Card* Deck::getNext() // pop a card off the stack and return it
{
	Card* c1 = cardDeck.pop();	
	return c1;
}

void Deck::print()
{
	cardDeck.print();
}	

