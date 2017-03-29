// Header file for the player class. Along with the game class this is the most important class
// All of the characters to be played inherit from this class
// An important note: this is an abstract class and cannot be instantiated

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Hand.h"
#include "Card.h"
#include "Requests.h"
#include "RequestQueue.h"
#include "Game.h"
#include "Deck.h"
using namespace std;

class Player
{
protected:
	friend class Hand;
	friend class RequestQueue;
	vector <Card*> pairs; // add pairs of cards as they come, prepare them for deletion
	RequestQueue* playerRequests;
	string identity;
	bool QueueSearch;
	int PlayerNumber;
	static int playerCount;
	static int roundCount;
public:
	Player();
	static bool gameOver;
	static string winnerSpecies;
	static int winnerNum;
	Hand current; // holds cards
	Player(int); // tell the queue how big it has to be
	void setIdentity(string);
	void removeCard(Card* c1);
	virtual void requestCard(Deck* d1, Game& g1); // ask what p2 has
	void receiveCard(Card* c1); // add to hand	
	virtual Card* drawCard(Deck* d1);
	bool checkEmpty(); // returns true if empty
	virtual bool checkForPairs(); // check this often, returns true if there are pairs after adding all the pairs to the vector and then clearing it. Should also print out what the pairs were
	void addRequest(Requests* req1); // add request to queue
	bool announceRemoval();
	bool foundSuccess;
	void incrementRoundCount();
	int getRoundCount();
	int getPlayerCount();
	void incrementPlayerCount();
	void setPlayerNumber();
	int getPlayerNumber();
	virtual Player* findPlayer(Card* sucCard, Game& g1); // define special for human and hydra
	string getIdentity();
	bool pairCheckerHelper(Card* c1, Card* c2);
	virtual Card* lookBack() = 0; // this function should only be called after at least one person has gone
};
	
	
#endif	
