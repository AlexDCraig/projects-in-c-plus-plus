// This class will be used to pit the Players against each other.

#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include <vector>
#include <string>
using namespace std;

class Player;


class Game
{
protected:
	Deck* gameDeck; // hold the stack of cards that players will draw from	
	int* PlayerNumbers;
public:
	Game(); // establish gamedeck by using Deck functions
	void addPlayers(); // add to activePlayers in this function
	vector <Player*> activePlayers; // vector holds each active player, erases them if the win, size = number of players
	void begin(); // uses deck functions to shuffle and then distribute 7 cards to each active player
	//friend void Player::drawCard(); // function to be used when a player asks go fish and doesn't get the card, pop a card off the gamedeck
	int getNumActive();
	bool checkVictory();
	void playGoFish();
	
};
	
#endif
