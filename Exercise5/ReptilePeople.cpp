// implementation file of reptilepeople

#include "ReptilePeople.h"
#include "Player.h"
#include "Card.h"
#include "Requests.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "Game.h"
#include <stdlib.h>
#include <string>
using namespace std;


ReptilePeople::ReptilePeople(int rosterSize)
{
	foundSuccess = false;
	setIdentity("ReptilePeople");
	playerRequests = new RequestQueue(rosterSize * 2); // tell the queue it has to be that big
}

// standard look back function except reptilepeople can only look back once in the buffer
Card* ReptilePeople::lookBack()
{
	vector <Card*> ideal; // get the cards with the highest count
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

	// ideal now holds the cards with the highest count

	vector <Requests*> compilation; // to put data back into the queue
	vector <Requests*> successPile;

	if (playerRequests->currentSize > 0)
	{
		for (int k = 0; k < 1; k++)
		{
			Requests* placeholder = playerRequests->dequeue();
			
			if (k == 0)
		{

			for (int r = 0; r < ideal.size(); r++)
			{
				if (placeholder->success == true && placeholder->rank == ideal.at(r)->rank && placeholder->askerNumber != PlayerNumber)
				{
					successPile.push_back(placeholder);
				}
			}
		}
			compilation.push_back(placeholder);
		}

	}		
	
	reverse(compilation.begin(), compilation.end());

	for (int j = 0; j < compilation.size(); j++)
	{
		playerRequests->enqueue(compilation.at(j));
	}

	Requests* successRequest = new Requests;
	Card* successCard = new Card;

	if (successPile.size() > 0) // if the last request was successful, ask for that card
	{
		successRequest = successPile.at(0);
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
		
void ReptilePeople::requestCard(Deck* d1, Game& g1) // for AI to use, used with gameDeck
{
	this->checkForPairs();
	
	Card* c1 = lookBack(); 

	Player* p2;

	if (QueueSearch == true)
	{
		p2 = findPlayer(c1, g1);
	}

	else
	{
		int size420 = g1.activePlayers.size();
		int randomPlayer = rand() % size420;

		randomPlayer = rand() % size420;

		while (g1.activePlayers.at(randomPlayer)->getPlayerNumber() == PlayerNumber)
		{
			randomPlayer = rand() % size420;
		}
		
		p2 = g1.activePlayers.at(randomPlayer);
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


