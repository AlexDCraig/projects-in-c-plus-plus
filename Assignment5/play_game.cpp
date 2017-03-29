#include "Card.h"
#include "DeckStack.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Gollum.h"
#include "BlueMen.h"
#include "Barbarian.h"
#include "Hydra.h"
#include "Human.h"
#include "ReptilePeople.h"
#include "Game.h"
#include <ctime>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

bool Player::gameOver = false; // this variable controls how long the game loop exists for
int Player::roundCount = 0;
int Player::playerCount = 0;
string Player:: winnerSpecies = "";
int Player:: winnerNum = 0;


int main()
{
	srand(time(0));
	
	Game GoFish;

	GoFish.addPlayers();

	GoFish.begin();

	GoFish.playGoFish();
	
	return 0;
}	
