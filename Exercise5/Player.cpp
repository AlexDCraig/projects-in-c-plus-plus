// implementation file for the player class

#include "Hand.h"
#include "Game.h"
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Gollum.h"
#include "Human.h"
#include "ReptilePeople.h"
#include "Hydra.h"
#include "ReptilePeople.h"
#include "BlueMen.h"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

Player::Player()
{
	identity = "";
	foundSuccess = false;
	QueueSearch = false;
}

Player::Player(int rosterSize) // make sure to send the number of players, not numplayers * 2
{
	playerRequests = new RequestQueue(rosterSize * 2);
}

// to be used in determining pairs of four
bool Player::pairCheckerHelper(Card* c1, Card* c2)
{
	if (c1->rank == c2->rank)
		return true;

	else
		return false;
}

// give away the card to another player, delete it from my data
void Player::removeCard(Card* c1)
{
	current.removeFromHand(c1);
	current.sortHand();
}

// add the pointer to the player's hand and then sort their hand
void Player::receiveCard(Card* c1)
{
	this->current.addToHand(c1);
	current.sortHand();
}

bool Player::checkEmpty()
{
	if (current.getHandSize() == 0)
		return true;

	else
		return false;
}

// uses the helper function above to find pairs of four
bool Player::checkForPairs()
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
			pairs.push_back(card1); // doesn't matter which card
			won = announceRemoval();			
			
			current.sortHand();			
			bool pure = true;

			for (int r = 0; r < current.cards.size(); r++) // start at the fourth match and move upwards into the first card that was a match
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
	// make this function find pairs, remove them from hand, pop onto vector, print out, and erase
}
	
void Player::addRequest(Requests* req1)
{
	playerRequests->enqueue(req1);
}

// this will be used to tell the screen that a player subclass has gotten a four pair
bool Player::announceRemoval() // The only time a player can win is after they've removed cards. This function returns true if the player's hand is empty.
{
	for (int k = 0; k < pairs.size(); k++)
	{
		Card* c = pairs.at(k);
		cout << identity << " has gotten four of a kind." << endl;
		cout << "The four that will be removed: Rank: " << c->rank << endl;
	}

	if (current.cards.empty() == false)
		return false;

	else if (current.cards.empty() == true)
		{
			winnerSpecies = this->getIdentity();
			winnerNum = this->getPlayerNumber();
			
			return true;
		}

}

Card* Player::drawCard(Deck* d1) // to be used with gamedeck from game
{
	d1->cardShuffle();
	Card* c1 = d1->getNext();
	receiveCard(c1); // add that card to the player's hand
	current.sortHand();
	return c1;
}

// use look back to find a card, then find out who the card belongs to, then ask them forit
void Player::requestCard(Deck* d1, Game& g1) // for AI to use, used with gameDeck
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
	r->haver = p2->getIdentity();
	r->askerNumber = PlayerNumber;
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
		p2->removeCard(c1); 
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

// used to search the buffer for the player who made a successful request for the card in question
Player* Player::findPlayer(Card* sucCard, Game& g1) // take the card from lookback and iterate thru to find the player who requested it and got it. only to be used if foundSuc=T
{
	vector <Requests*> compilation; // to put data back into the queue
	Player* targetPlayer;
	string targetName;

	for (int k = 0; k < playerRequests->currentSize; k++) // search through the buffer
	{
		Requests* placeholder = playerRequests->dequeue(); 
		
		if (placeholder->rank == sucCard->rank && placeholder->success == true && placeholder->askerNumber != PlayerNumber)
			targetName = placeholder->asker;

		compilation.push_back(placeholder);
	}		
	
	for (int j = 0; j < g1.activePlayers.size(); j++)
	{
		if (targetName == g1.activePlayers.at(j)->getIdentity() && g1.activePlayers.at(j)->getPlayerNumber() != PlayerNumber)
			targetPlayer = g1.activePlayers.at(j);
	}	
	
	// sort vector
	reverse(compilation.begin(), compilation.end());

	for (int j = 0; j < compilation.size(); j++) // put requests back into the queue in proper order
	{
		playerRequests->enqueue(compilation.at(j));
	}

	return targetPlayer;

}

void Player::setIdentity(string id)
{
	identity = id;
}

string Player::getIdentity()
{
	return identity;
}

void Player:: incrementRoundCount()
{
	roundCount++;
}

int Player:: getRoundCount()
{
	return roundCount;
}

int Player:: getPlayerCount()
{
	return playerCount;
}

void Player:: incrementPlayerCount()
{
	playerCount++;
}

void Player:: setPlayerNumber()
{
	incrementPlayerCount();
	PlayerNumber = playerCount;
}

int Player:: getPlayerNumber()
{
	return PlayerNumber;
}
