// Implementation file of the Human class.

#include "Human.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

Human::Human(int rosterSize)
{
	setIdentity("Human");
	playerRequests = new RequestQueue(rosterSize * 2); // tell the queue it has to be that big
	foundSuccess = false;
}

// In general the requestCard functions of the subclasses are the same. However this is not the case for this class.
// Rather than having his decisions made for him a la Gollum, the Human will have everything printed out for them
// and will be expected to interact with the AI using his keyboard.
void Human::requestCard(Deck* d1, Game& g1)
{
	cout << "Choose the number corresponding to one of the following active players to request a card from: " << endl;

	for (int k = 0; k < g1.activePlayers.size(); k++)
	{	
		if (g1.activePlayers.at(k)->getPlayerNumber() != PlayerNumber)
		cout << (k + 1) << ": " << g1.activePlayers.at(k)->getIdentity() << endl;
	}

	int playNum;

	cin >> playNum;

	Player* requestee = g1.activePlayers.at(playNum - 1); // get the address to the player they want

	bool luckyBlue = false; // will be used to determine the bluemen's 5% chance of lying

	if (requestee->getIdentity() == "BlueMen")
	{
		int bluesLucky = rand() % 100 + 1; 

		if (bluesLucky <= 5) // if 5 percent chance met
		{
			cout << "BlueMen will be lying no matter what about their card this round." << endl;
			luckyBlue = true;
		}
	}
		
	cout << "You have the following cards. Choose the number corresponding to the card you'd like to ask " << requestee->getIdentity() << " for." << endl;
	
	for (int r = 0; r < current.getHandSize(); r++)
	{
		Card* c1 = current.cards.at(r);
		cout << r + 1 << ": " << c1->rank << " of " << c1->suit << endl;
	}

	int cardNum;
	
	cin >> cardNum;

	Card* chosen = current.cards.at(cardNum - 1);

	bool has;
	has = requestee->current.hasCard(chosen); // if p2 has the card then this will return true

	if (luckyBlue == true)
		has = false;

	Requests* r = new Requests;
	r->asker = identity; // the person who asked for the card, they must have one
	r->haver = requestee->getIdentity();
	r->suit = chosen->suit;
	r->rank = chosen->rank;
	r->success = has; // whether they had it or not

	for (int k = 0; k < g1.activePlayers.size(); k++)
	{
		if (g1.activePlayers.at(k)->getIdentity() != "Human" && g1.activePlayers.at(k)->getIdentity() != "Hydra")
			g1.activePlayers.at(k)->addRequest(r);
	}

	if (has == true)
	{
		cout << identity << " has requested a " << chosen->rank << " from the " << requestee->getIdentity() << " and they had it." << endl;
		requestee->removeCard(chosen); // p2 must give card to the caller of this function
		current.cards.push_back(chosen); // caller gets the card
		this->checkForPairs();
	}

	else
	{
		cout << identity << " requested a " << chosen->rank << " from the " << requestee->getIdentity() <<  " but was unable to get it." << endl;
		Card* c2 = this->drawCard(d1);
		cout << identity << " has drawn a " << c2->rank << " of " << c2->suit << "." << endl;;
		this->checkForPairs();
	}				
}

// this function is used exclusively to serve the purpose of fulfilling the pure virtual requirement. It returns a phony card that won't be used.
// This function is not used because the human can't look back.
Card* Human::lookBack()
{
	Card* falseCard = new Card;
	falseCard->rank = "2";
	falseCard->suit = "hearts";	
	cout << "The human cannot look back." << endl;
	return falseCard;
}
