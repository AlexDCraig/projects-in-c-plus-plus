// implementation file for the hydra class, a subclass of player
#include "Hydra.h"
#include "Card.h"
#include "Deck.h"
#include "Requests.h"
#include <vector>
#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

Hydra::Hydra(int rosterSize)
{
	setIdentity("Hydra");
	foundSuccess = false;
	playerRequests = new RequestQueue(0); // tell the queue it has to be that big
}

// this function is not standard of the other classes. hydra doesn't do anything but draw cards
void Hydra::requestCard(Deck* d1, Game& g1) // for AI to use
{
	Card* falseCard = lookBack();
	cout << "The Hydra hisses ferociously at first, and then whimpers a second time. For it cannot speak, and this game of GoFish nothing but a cruel reminder of its most unfortunate shortcoming. The Hydra is forced to take a card." << endl;	
	drawCard(d1);
}
// phony function, doesn't do anything besides satisfy the pure virtual function requirement
Card* Hydra::lookBack()
{
	cout << "The Hydra can't look back." << endl;
	Card* falseCard = new Card;
	falseCard->rank = "2";
	falseCard->suit = "hearts";
	return falseCard;
}
