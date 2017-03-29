// Header file for the Human subclass of Player. this class, unlike the other subclasses,
// will be controlled by a real living being.

#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"

class Human : public Player
{
public:
	Human(int);
	void requestCard(Deck* d1, Game& g1);
	Card* lookBack();
};

#endif
