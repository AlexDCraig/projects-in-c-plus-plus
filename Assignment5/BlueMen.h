// Class: BlueMen. 

#ifndef BLUEMEN_H
#define BLUEMEN_H

#include "Player.h"
#include "Card.h"

class BlueMen : public Player
{
public:
	BlueMen(int);
	Card* lookBack();
	bool checkForPairs();
};

#endif
