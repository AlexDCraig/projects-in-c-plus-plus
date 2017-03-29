// Implementation of Gollum header file

#include "Gollum.h"
#include "Player.h"
#include "Card.h"
#include "Requests.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Game.h"
#include "Hand.h"
#include <stdlib.h>
#include <string>
using namespace std;

Gollum::Gollum(int rosterSize)
{
	setIdentity("Gollum");
	foundSuccess = false;
	playerRequests = new RequestQueue(rosterSize * 2); // tell the queue it has to be that big
}

// This function is pure virtual and so each subclass of player is forced to define it. 
// Gollum's method of finding the perfect card is basically the same, but he is 
// able to search the entire buffer. This makes Gollum a very powerful character.
Card* Gollum::lookBack() // get successes, sort them by recency
{

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

	if (playerRequests->currentSize > 1)
	{
		for (int k = 0; k < playerRequests->currentSize; k++) // search through the buffer
		{
			Requests* placeholder = playerRequests->dequeue(); 
		
			for (int x = 0; x < ideal.size(); x++)
			{
				if (placeholder->success == true && placeholder->rank == ideal.at(x)->rank && placeholder->askerNumber != PlayerNumber) // if the card request was successful and matches gollum's high card
				{
					successPile.push_back(placeholder);
				}
			}
			compilation.push_back(placeholder);
		}
		
		// sort both vectors by recency
		reverse(successPile.begin(), successPile.end());
		reverse(compilation.begin(), compilation.end());

		for (int j = 0; j < compilation.size(); j++) // put the player requests back after dequeing
		{
			playerRequests->enqueue(compilation.at(j));
		}

	}		
	
	Requests* successRequest = new Requests;
	Card* successCard = new Card;

	if (successPile.size() > 0) // if at least one request for a good card was successful
	{
			int element = rand() % successPile.size();

			while (successPile.at(element)->askerNumber == PlayerNumber)
				element = rand() % successPile.size();

			successRequest = successPile.at(element); // the most recent card requested successfully
			successCard->suit = successRequest->suit;
			successCard->rank = successRequest->rank;
			foundSuccess = true;
			QueueSearch = true;
	}

	else // nothing in the queue matches a max card from gollum's hand, so ask for a random one
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
						
	return successCard; // returns the card gollum needs most that is found in the queue
}

// Standard function in all the subclasses.
void Gollum::requestCard(Deck* d1, Game& g1) // for AI to use, used with gameDeck
{
	this->checkForPairs();

	Card* c1 = lookBack(); 
	Player* p2;
	
	if (QueueSearch == true) // if the lookBack generated something useful
	{
		p2 = findPlayer(c1, g1);
	}

	else // request the card from somebody random
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
		Card* c2 = this->drawCard(d1);
		cout << identity << " has drawn a " << c2->rank << " of " << c2->suit << "." << endl;
		this->checkForPairs();
		p2->checkForPairs();
	}

	if (current.cards.empty() == true)
		gameOver = true;			

	this->checkForPairs();	
}			
