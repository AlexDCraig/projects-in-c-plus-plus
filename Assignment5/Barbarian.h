/* Class: Barbarian
 * Character that inherits from the Player class.
 */

#ifndef BARBARIAN_H
#define BARBARIAN_H

#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Game.h"

class Barbarian : public Player
{
public:
	Barbarian(int);
	Card* drawCard(Deck* d1);
	Card* lookBack();
	void requestCard(Deck* d1,Game& g1);
};

#endif
