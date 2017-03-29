// Header file for Hydra, the subclass of player that can do nothing but offer up her cards and take cards from the deck

#ifndef HYDRA_H
#define HYDRA_H

#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Game.h"

class Hydra : public Player
{
public:
	Hydra();
	Hydra(int);
	void requestCard(Deck* d1, Game& g1);
	Card* lookBack();
};

#endif
