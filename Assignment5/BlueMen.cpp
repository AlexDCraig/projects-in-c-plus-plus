#include "BlueMen.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Requests.h"
#include "RequestQueue.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

BlueMen::BlueMen(int rosterSize)
{
	setIdentity("BlueMen");
	foundSuccess = false;
	playerRequests = new RequestQueue(rosterSize * 2); // tell the queue it has to be that big
}

// See the Barbarian comment for a full description. BlueMen's look back is the same as Barbarian's,
// he can look through half the buffer and makes an educated decision based on his search.
Card* BlueMen::lookBack()
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
	int numAc = getPlayerCount();

if (playerRequests->currentSize > 1)
{
	for (int k = 0; k < playerRequests->currentSize; k++) // search through half of the buffer
	{
		Requests* placeholder = playerRequests->dequeue(); 
	
		if (k < numAc)		
	{
		for (int x = 0; x < ideal.size(); x++)
		{
			if (placeholder->success == true && placeholder->rank == ideal.at(x)->rank && placeholder->askerNumber != PlayerNumber) // if the card request was successful and matches gollum's high card
			{
				successPile.push_back(placeholder);
			}
		}
	}

		compilation.push_back(placeholder);
	}		
	
	// sort both vectors by recency
	reverse(successPile.begin(), successPile.end());
	reverse(compilation.begin(), compilation.end());

	for (int j = 0; j < compilation.size(); j++)
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
			int element = rand() % successPile.size();
			successCard->rank = ideal.at(element)->rank;
			successCard->suit = ideal.at(element)->suit;
			QueueSearch = false;
		}

		else
		{
			int el = rand() % current.cards.size();
			successCard->rank = current.cards.at(el)->rank;
			successCard->suit = current.cards.at(el)->suit;
			QueueSearch =false;
		}
	}

	return successCard; 	

}

// this virtual function is unique to BlueMen because he is able to lie about having four cards when he just has three. The first half
// of this function is identical to the one in Player and the second half is similar, it just looks for three cards
bool BlueMen::checkForPairs()
{
	current.sortHand(); // put the cards in order

	bool found = false;

	int counter = 1;

	bool won = false;

	vector <Card*> tempVec;

	if (current.getHandSize() == 4)
	{
		if (current.cards.at(0)->rank == current.cards.at(1)->rank && current.cards.at(1)->rank == current.cards.at(2)->rank && current.cards.at(2)->rank == current.cards.at(3)->rank)
		{
			announceRemoval();
			gameOver = true;
			won = true;
			found = true;
			winnerSpecies = this->getIdentity();
			winnerNum = this->getPlayerNumber();
			current.cards.clear();
			
			return found;
		}

	}

	for (int k = current.getHandSize() - 1; k > 0; k--)
	{
		Card* card1 = current.cards.at(k);
		Card* card2 = current.cards.at(k - 1);

		if (pairCheckerHelper(card1, card2) == true)
			counter++;

		else
			counter = 1;

		if (counter == 4)
		{
			found = true;
			pairs.push_back(card1);
			won = announceRemoval();
			
			current.sortHand();
			bool pure = true;

			for (int r = 0; r < current.cards.size(); r++)
			{
				for (int j = 0; j < pairs.size(); j++)
				{
					if (current.cards.at(r)->rank == pairs.at(j)->rank)
						pure = false;
				}
			
			if (pure == true)
				tempVec.push_back(current.cards.at(k));
			
			pure = true;
			
			}


		}
	}

if (tempVec.size() > 0 && current.cards.size() > 0)
{
	current.cards.clear();
	
	for (int k = 0; k < tempVec.size(); k++)
	{
		current.cards.push_back(tempVec.at(k));
	}

	current.sortHand();

}

	pairs.clear();
	tempVec.clear();

	counter = 1;

	for (int k = current.getHandSize() - 1; k > 0; k--)
	{
		Card* card1 = current.cards.at(k);
		Card* card2 = current.cards.at(k - 1);

		if (pairCheckerHelper(card1, card2) == true)
		{
			counter++;

			Card* card3 = current.cards.at(k - 2);
			
			if (card3->rank == card2->rank)
				counter++;
			else
				counter = 1;
		}

		else
			counter = 1;

		if (counter == 3)
		{
			found = true;
			pairs.push_back(card1);
			won = announceRemoval();
			
			current.sortHand();
			bool pure = true;

			for (int r = 0; r < current.cards.size(); r++)
			{
				for (int j = 0; j < pairs.size(); j++)
				{
					if (current.cards.at(r)->rank == pairs.at(j)->rank)
						pure = false;
				}
			
			if (pure == true)
				tempVec.push_back(current.cards.at(r));
			
			pure = true;
			}
		}

if (tempVec.size() > 0 && current.cards.size() > 0)
{
	current.cards.clear();
	
	for (int k = 0; k < tempVec.size(); k++)
	{
		current.cards.push_back(tempVec.at(k));
	}

	current.sortHand();
}

	pairs.clear();

	if (won == true)
	{
		gameOver = true;
		winnerSpecies = this->getIdentity();
		winnerNum = this->getPlayerNumber();
	}		
	

	return found;

}
}

