/** Lays out the bread and butter class of the Game: Player. Two objects
 * of this class will be instantiated, two container classes will be used to 
 * collect two rosters, and these rosters will be manipulated using the Creature
 * battle function to determine the winners and losers in a tournament
 */

#ifndef PLAY_H
#define PLAY_H

#include "Creat.h"
#include "Blue.h"
#include "Barb.h"
#include "Gollum.h"
#include "Hydra.h"
#include "ReptilePeople.h"
#include "LineQueue.h"
#include "StandingsStack.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

class Player
{
private:
	friend class LineupQueue;
	friend class StandingsStack;
	LineupQueue* roster;
	LineupQueue* winners;
	LineupQueue* losers;
	StandingsStack* fullList;
	bool isFirst;
	int timesKilledEnemy;
	int timesBeenKilledByEnemy;
protected:
	static int rosterSize; // static because all players have same #
	string teamName;
	int deaths;
	int kills;
public:
	Player(int, string);
	~Player(); // delete the roster
	void fillRoster();
	void battle(Player*);
	StandingsStack* winnersBracket(Player*);
	void printRoster();
	void printWinners();
	void printLosers();
	void printStack();
	void printFinal(Player*);
	StandingsStack* calculateTopThree(LineupQueue*);
	string getTeamName();
	int getDeaths();
	int getKills();
};	

#endif
