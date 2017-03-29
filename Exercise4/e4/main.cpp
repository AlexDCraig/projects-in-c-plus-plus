#include "Creat.h"
#include "Blue.h"
#include "Barb.h"
#include "Goll.h"
#include "Hy.h"
#include "RepPpl.h"
#include "Play.h"
#include "StandingsStack.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

// Declaration of all static members used
int Player::rosterSize = 0;
//int Barbarian::timesKilled = 0;
//int Barbarian::timesBeenKilled = 0;
bool Barbarian::hasPlayed = false;
//int BlueMen::timesKilled = 0;
//int BlueMen::timesBeenKilled = 0;
bool BlueMen::hasPlayed = false;
//int Gollum::timesKilled = 0;
//int Gollum::timesBeenKilled = 0;
bool Gollum::hasPlayed = false;
//int Hydra::timesKilled = 0;
//int Hydra::timesBeenKilled = 0;
bool Hydra::hasPlayed = false;
//int ReptilePeople::timesKilled = 0;
//int ReptilePeople::timesBeenKilled = 0;
bool ReptilePeople::hasPlayed = false;

int main()
{
	srand(time(0));
	string player1, player2;
	cout << "What is Player One's team name?" << endl;
	cin >> player1;
	cout << "What is Player Two's team name?" << endl;
	cin >> player2;
	cout << "Please provide the number of combatants for both teams." << endl;
	int num;
	cin >> num;
	Player p1(num, player1);
	Player p2(num, player2);
	p1.fillRoster();
	cout << endl;
	p1.printRoster();
	p2.fillRoster();
	cout << endl;
	p2.printRoster();
	p1.battle(&p2);
	StandingsStack* s1;
	s1 = p1.winnersBracket(&p2);
	cout << endl << "The top 3 victors in terms of kills:  " << endl;
	cout << endl;
	s1->printList();
	cout << endl << endl << "The rest of the competitors: " << endl;
	p1.printStack();
	cout << endl;
	p1.printFinal(&p2);	
	

	return 0;
}

