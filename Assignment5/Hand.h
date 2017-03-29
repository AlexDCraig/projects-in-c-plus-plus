// Header file for the Hand class. This will be used to hold a player's personalized set of cards

#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

using namespace std;

class Hand
{
protected:
	friend class Player;
	int handSize;
public:
	Hand();
	vector <Card*> cards;
	void addToHand(Card* c1);
	Card* removeFromHand(Card* c1);
	int getHandSize();
	void sortHand();
	bool hasCard(Card* ca);
};

#endif
