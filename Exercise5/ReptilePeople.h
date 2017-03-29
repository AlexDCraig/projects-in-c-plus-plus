// header file for reptilepeople, a subclass of player

#ifndef REPTILEPEOPLE_H
#define REPTILEPEOPLE_H

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"

class ReptilePeople : public Player
{
public:
	ReptilePeople(int);
	Card* lookBack();
	void requestCard(Deck* d1, Game& g1);
};

#endif
