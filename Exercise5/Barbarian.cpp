/* Implementation of Barbarian class. */

#include "Barbarian.h"
#include "RequestQueue.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Requests.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

Barbarian::Barbarian(int siz)
{
	setIdentity("Barbarian");
	foundSuccess = false;
	playerRequests = new RequestQueue(siz * 2); // allocate memory for the RequestQueue to be used as a buffer
}

// Takes a pointer to a Deck and uses that Deck to generate a new card to add to Barbarian's hand.
// Important to note that this function always comes up twice with the Barbarian because he draws two cards.
Card* Barbarian::drawCard(Deck* d1)
{	
	d1->cardShuffle();
	Card* c1 = new Card;
	c1 = d1->getNext();
	receiveCard(c1); // add that card to the player's hand
	current.sortHand();
	return c1;
}	

// Barbarian's way of searching the buffer. 
// Searches through his cards and finds the cards that have the highest count.
// Then he looks through the buffer to see if the cards were successfully requested recently.
// If they weren't, he just asks for a random card from his highest counted cards.
Card* Barbarian::lookBack() // get successes, sort them by recency
{
	this->checkForPairs();

	vector <Card*> ideal; // to hold possible cards
	int currentCount = 1;
	int highestCount = 1;
	
	
	for (int k = 0; k < current.getHandSize() - 2; k++) // find the cards that have the highest count
	{
		if (current.cards.at(k)->rank == current.cards.at(k+1)->rank)
			{
				currentCount++;
	
				if (currentCount >= highestCount)
				{
					Card* winner = new Card;
					winner->rank = current.cards.at(k)->rank;
					ideal.push_back(winner);
					highestCount = currentCount;
				}
			}
	
		else if (current.cards.at(k)->rank != current.cards.at(k+1)->rank)
			currentCount = 1;
	}

	vector <Requests*> successPile; // need only concern himself with the requests previously that were successful because that means someone has it
	vector <Requests*> compilation; // to put data back into the queue

	int numAc = getPlayerCount();

	if (playerRequests->currentSize > 1)
	{
		for (int k =0; k < playerRequests->currentSize; k++)
		{
			Requests* placeholder = playerRequests->dequeue();
				
			if (k < numAc)
		{
			for (int x = 0; x < ideal.size(); x++)
			{
				if (placeholder->success == true && placeholder->rank == ideal.at(x)->rank && placeholder->askerNumber != PlayerNumber)
				{
					successPile.push_back(placeholder);
				}
			}
		}
		
			compilation.push_back(placeholder);
		}

		reverse(successPile.begin(), successPile.end());
		reverse(compilation.begin(), compilation.end());

		for (int j = 0; j < compilation.size(); j++)
		{
			playerRequests->enqueue(compilation.at(j));
		}
	}

	Requests* successRequest = new Requests;
	Card* successCard = new Card;

	if (successPile.size() > 0)
	{
		int element = rand() % successPile.size();
		
		while (successPile.at(element)->askerNumber == PlayerNumber)
			element = rand() % successPile.size();
		
		successRequest = successPile.at(element);
		successCard->suit = successRequest->suit;
		successCard->rank = successRequest->rank;
		foundSuccess = true;
		QueueSearch = true;
	}

	else
	{
		if (ideal.size() > 0)
		{
			int element = rand() % ideal.size();
			successCard->rank = ideal.at(element)->rank;
			successCard->suit = ideal.at(element)->suit;
			QueueSearch = false;
		}

		else
		{
			int el = rand() % current.cards.size();
			successCard->rank = current.cards.at(el)->rank;
			successCard->suit = current.cards.at(el)->suit;
			QueueSearch = false;
		}
	}

	return successCard;
}

// Takes a pointer to a Deck and a reference to the Game itself. Uses look back to get a card to look for.
// If the card was found in the buffer he then searches for who asked for it.
// otherwise, he just asks a random player. The function then reports whether the card was successfully
// requested or not.
void Barbarian::requestCard(Deck* d1, Game& g1) // for AI to use, used with gameDeck
{
	this->checkForPairs();

	Card* c1 = lookBack(); 

	Player* p2;

	if (QueueSearch == true)
	{
		p2 = findPlayer(c1,g1);
	}

	else
	{
		int size1 = g1.activePlayers.size();
		int randomPlay = rand() % size1;

		while (g1.activePlayers.at(randomPlay)->getPlayerNumber() == PlayerNumber)
		{
			randomPlay = rand() % size1;
		}

		p2 = g1.activePlayers.at(randomPlay);
	}

	bool luckyBlue = false; // will be used to determine the bluemen's 5% chance of lying
	
	if (p2->getIdentity() == "BlueMen")
	{
		int bluesLucky = rand() % 100 + 1; 

		if (bluesLucky <= 5) // if 5 percent chance met
		{
			cout << "BlueMen will be lying no matter what about their card this round." << endl;
			luckyBlue = true;
		}
	}
		
	bool has;
	has = p2->current.hasCard(c1); // if p2 has the card then this will return true

	if (luckyBlue == true)
		has = false;

	Requests* r = new Requests;
	r->asker = identity; // the person who asked for the card, they must have one
	r->askerNumber = PlayerNumber;
	r->haver = p2->getIdentity();
	r->suit = c1->suit;
	r->rank = c1->rank;
	r->success = has; // whether they had it or not

	for (int k = 0; k < g1.activePlayers.size(); k++)
	{
		if (g1.activePlayers.at(k)->getIdentity() != "Human" && g1.activePlayers.at(k)->getIdentity() != "Hydra")
			g1.activePlayers.at(k)->addRequest(r);
	}

	if (has == true)
	{
		cout << identity << " has requested a " << c1->rank << " from the " << p2->getIdentity() << " and they had it." << endl;
		p2->removeCard(c1); // p2 must give card to the caller of this function
		receiveCard(c1);
		this->checkForPairs();
		p2->checkForPairs();
	}

	else
	{
		cout << identity << " requested a " << c1->rank << " from the " << p2->getIdentity() <<  " but was unable to get it." << endl;
		if (current.cards.size() < 10)
		{
			Card* c2 = this->drawCard(d1);
			cout << identity << " has drawn a " << c2->rank << " of " << c2->suit << "." << endl;
		}

		if (current.cards.size() < 10)
		{
			Card* c3 = this->drawCard(d1);
			cout << identity << " has drawn a " << c3->rank << " of " << c3->suit << "." << endl;
		}

		this->checkForPairs();
		p2->checkForPairs();
	}

	if (current.cards.empty() == true)
		gameOver = true;

	this->checkForPairs();	
}
