#ifndef GOLLUM_H
#define GOLLUM_H

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"

class Gollum : public Player
{
public:	
	Gollum(int);
	Card* lookBack(); // define pure virtual
	void requestCard(Deck* d1, Game& g1);
};

#endif
