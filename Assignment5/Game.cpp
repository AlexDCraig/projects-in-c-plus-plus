// Implementation of the Game class.

#include "Game.h"
#include "Gollum.h"
#include "Barbarian.h"
#include "ReptilePeople.h"
#include "BlueMen.h"
#include "Hydra.h"
#include "Human.h"
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


Game::Game()
{
	gameDeck = new Deck; // dynamically allocate the cards that will be used for the game
	gameDeck->assembleDeck(); // initialize gameDeck, Deck object
	gameDeck->cardShuffle(); // shuffle the cards, place them onto stack
}

// First step: Get the player types for a roster of players who will be playing.
void Game::addPlayers()
{

	cout << "Please enter the number of players for the game." << endl;
	int num;
	cin >> num;

	if (num < 2 || num > 7) // there can only be 2-7 players
	{
		cout << "There must be 2-7 players to play." << endl;
		exit(1);
	}

	PlayerNumbers = new int[num];

	for (int k = 0; k < num; k++) // this is where players will be added to the activePlayers vector. it will take the information of the players
	{
		cout << "Enter the number corresponding to a player type: 1. Gollum. 2. Barbarian. 3. ReptilePeople. 4. BlueMen. 5. Hydra. 6. Human." << endl;
		int user;
		cin >> user;
	
		if (user == 1)
		{
			Player* g1 = new Gollum(num);
			activePlayers.push_back(g1);
			PlayerNumbers[k] = k;
			g1->setPlayerNumber();			
		}
		
		else if (user == 2)
		{
			Player* b1 = new Barbarian(num);
			activePlayers.push_back(b1);
			PlayerNumbers[k] = k;
			b1->setPlayerNumber();
		}

		else if (user == 3)
		{
			Player* r1 = new ReptilePeople(num);
			activePlayers.push_back(r1);
			PlayerNumbers[k] = k;
			r1->setPlayerNumber();
		}

		else if (user == 4)
		{
			Player* bm1 = new BlueMen(num);
			activePlayers.push_back(bm1);
			PlayerNumbers[k] = k;
			bm1->setPlayerNumber();
		}

		else if (user == 5)
		{
			Player* h1 = new Hydra(num);
			activePlayers.push_back(h1);
			PlayerNumbers[k] = k;
			h1->setPlayerNumber();
		}

		else if (user == 6)
		{
			Player* hu1 = new Human(num);
			activePlayers.push_back(hu1);
			PlayerNumbers[k] = k;
			hu1->setPlayerNumber();
		}
	}
}

// Step 2 of the Game: shuffle up the deck of cards and then give each player 7 cards.
void Game::begin()
{
	gameDeck->cardShuffle();
	
	for (int k = 0; k < activePlayers.size(); k++)
	{
		for (int j = 0; j < 7; j++)
		{
			activePlayers.at(k)->drawCard(gameDeck);	
		}
	}
	
}

// this will be used as a loop condition in play_game.cpp to determine whether the game should continue
// there are actually multiple checks for whether somebody has won
bool Game::checkVictory()
{
	bool victory = false;

	for (int r = 0; r < activePlayers.size(); r++)
	{
		if (activePlayers.at(r)->current.cards.empty() == true)
			victory = true;
	}

	return victory;
}

// The meat of the program. This function loops through all active Players until one wins, making each request a card in succession.
// The requestCard function does a lot of heavy lifting.
void Game::playGoFish()
{
	while (checkVictory() == false || activePlayers.at(0)->gameOver == false)
	{
		for (int j = 0; j < activePlayers.size(); j++)
		{
			activePlayers.at(j)->checkForPairs();
			activePlayers.at(0)->incrementRoundCount();
			cout << endl <<  "***It is Player Number " << PlayerNumbers[j] + 1 << ", the " <<  activePlayers.at(j)->getIdentity() << "'s turn.***" << endl;
			activePlayers.at(j)->requestCard(gameDeck, *this);
		}
	}

	cout << activePlayers.at(0)->winnerSpecies << ", player " << activePlayers.at(0)->winnerNum << ", has won." << endl;
	
}

int Game::getNumActive()
{
	int size = activePlayers.size();
	return size;
}	
