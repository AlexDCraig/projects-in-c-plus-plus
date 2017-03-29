#include "Play.h"
#include "Creat.h"
#include "LineQueue.h"
#include <iostream>
#include <time.h>
#include <string>
using namespace std;

Player::Player(int num, string team)
{
	rosterSize = num;
	teamName = team;
	timesKilledEnemy = 0;
	timesBeenKilledByEnemy = 0;
	//srand(time(0));
	
}

Player::~Player()
{
	roster->deleteAll(); // uses lineupqueue's deleteAll function to erase all data for each member
	winners->deleteAll();
	losers->deleteAll();
}

void Player::fillRoster()
{
	roster = new LineupQueue;

	//for testing
	Creature* g1 = new Gollum;
	g1->setName("gollum1");
	g1->setOwner(this->getTeamName());
	Creature* g2 = new Gollum;
	g2->setName("gollum2");
	g2->setOwner(this->getTeamName());
	Creature* g3 = new Hydra;
	g3->setName("gollum3");
	g3->setOwner(this->getTeamName());
	Creature* g4 = new Hydra;
	g4->setName("gollum4");
	g4->setOwner(this->getTeamName());
	Creature* g5 = new BlueMen;
	g5->setName("gollum5");
	g5->setOwner(this->getTeamName());
	Creature* g6 = new BlueMen;
	g6->setName("gollum6");
	g6->setOwner(this->getTeamName());
	Creature* g7 = new ReptilePeople;
	g7->setName("gollum7");
	g7->setOwner(this->getTeamName());
	Creature* g8 = new Barbarian;
	g8->setName("gollum8");
	g8->setOwner(this->getTeamName());


	Creature* g9 = new Gollum;
	g9->setName("gollum9");
	g9->setOwner(this->getTeamName());
	Creature* g10 = new Gollum;
	g10->setName("gollum10");
	g10->setOwner(this->getTeamName());
	Creature* g11 = new Hydra;
	g11->setName("gollum11");
	g11->setOwner(this->getTeamName());
	Creature* g12 = new Hydra;
	g12->setName("gollum12");
	g12->setOwner(this->getTeamName());
	Creature* g13 = new BlueMen;
	g13->setName("gollum13");
	g13->setOwner(this->getTeamName());
	Creature* g14 = new BlueMen;
	g14->setName("gollum14");
	g14->setOwner(this->getTeamName());
	Creature* g15 = new ReptilePeople;
	g15->setName("gollum15");
	g15->setOwner(this->getTeamName());
	Creature* g16 = new Barbarian;
	g16->setName("gollum16");
	g16->setOwner(this->getTeamName());
	
	roster->enqueue(g1);
	roster->enqueue(g2);
	roster->enqueue(g3);
	roster->enqueue(g4);
	roster->enqueue(g5);
	roster->enqueue(g6);
	roster->enqueue(g7);
	roster->enqueue(g8);
	roster->enqueue(g9);
	roster->enqueue(g10);
	roster->enqueue(g11);
	roster->enqueue(g12);
	roster->enqueue(g13);
	roster->enqueue(g14);
	roster->enqueue(g15);
	roster->enqueue(g16);

	/*cout << "There are the following creature types: Gollum, Barbarian, ReptilePeople, BlueMen, Hydra." << endl;
	
	cout << endl << "Please enter the creatures you would like for your team. The first creature you select will be the first creature to fight, the second creature will be the second to fight, and so on." << endl;

	for (int k = 0; k < rosterSize; k++)
	{
		cout << "For roster slot " << k + 1 << ":" << endl;
		string user;
		cin >> user;
		
		if (user == "Gollum" || user == "gollum")
			{
				Creature* g1 = new Gollum;
				cout << "Please assign it a unique name." << endl;
				string uniq;
				cin >> uniq;
				g1->setName(uniq);
				roster->enqueue(g1);
			}

		else if (user == "Barbarian" || user == "barbarian")
			{
				Creature* b1 = new Barbarian;
				cout << "Please assign it a unique name." << endl;
				string uniq;
				cin >> uniq;
				b1->setName(uniq);
				roster->enqueue(b1);
			}

		else if (user == "ReptilePeople" || user == "Reptilepeople" || user == "reptilepeople" || user == "reptilePeople")
			{
				Creature* r1 = new ReptilePeople;
			        cout << "Please assign it a unique name." << endl;
				string uniq;
				cin >> uniq;
				r1->setName(uniq);	
				roster->enqueue(r1);
			}

		else if (user == "BlueMen" || user == "Bluemen" || user == "bluemen" || user == "blueMen")
			{
				Creature* bm1 = new BlueMen;
				cout << "Assign it a unique name." << endl;
				string uniq;
				cin >> uniq;
				bm1->setName(uniq);
				roster->enqueue(bm1);
			}

		else if (user == "Hydra" || user == "hydra")
			{
				Creature* h1 = new Hydra;
				cout << "Give it a unique name." << endl;
				string uniq;
				cin >> uniq;
				h1->setName(uniq);
				roster->enqueue(h1);
			}

		else
		{
			cout << "ERROR: Invalid input." << endl;
			this->fillRoster();
		}


	}*/
}

void Player::battle(Player* p2)
{
	this->winners = new LineupQueue;
	this->losers = new LineupQueue;
	p2->winners = new LineupQueue;
	p2->losers = new LineupQueue;
	fullList = new StandingsStack;

	int counter = 1;

	for (int k = 0; k < rosterSize; k++) // both players have the same # of creatures. pair each creature up, see who wins, see who loses
	{
		Creature* play1 = this->roster->dequeue(); // pop off the first creature from the queue
		Creature* play2 = p2->roster->dequeue();
			
		while (play1->getStrengthPoints() > 0 && play2->getStrengthPoints() > 0)

		{	
			cout << "------ ROUND " << counter << " ------" << endl;

			
			play1->attackCreature(play2);
			play2->attackCreature(play1);
				
			counter++;
		}	

		if (play1->getStrengthPoints() == 0) // ASSUMES BOTH PLAYERS CANNOT DIE. If player1's creature dies, add that creature to the losers queue,
		// and add player2's creature to the winners queue
		{
			this->losers->enqueue(play1);
			timesBeenKilledByEnemy++;
			fullList->push(play1);
			p2->winners->enqueue(play2);
			p2->timesKilledEnemy++;
			play2->regenHealth();
		}

		else if (play2->getStrengthPoints() == 0)
		{
			p2->losers->enqueue(play2);
			timesKilledEnemy++;
			fullList->push(play2);
			this->winners->enqueue(play1);
			p2->timesBeenKilledByEnemy++;
			play1->regenHealth();
		}		

	}

	this->printWinners();
	this->printLosers();
	p2->printWinners();
	p2->printLosers();
}

StandingsStack* Player::winnersBracket(Player *p2) // pass other player's loser's bracket
{
	LineupQueue* topthree = new LineupQueue;
	
	cout << endl << "------ WINNER'S BRACKET ------" << endl;

	int playerOneSize = this->winners->returnSize();
	int playerTwoSize = this->winners->returnSize();

	if (playerOneSize == 0)
		{
			cout << this->getTeamName() << "  had no winners, therefore the winners are all those who won once belonging to the team " << p2->getTeamName() << "." << endl;
			// so all of the other team's winners are the top competitors
			//int counter = 0;
			
			while (p2->winners->checkEmpty() != true)
				{
					Creature* c1 = p2->winners->dequeue();
					topthree->enqueue(c1);
					//counter++;
				}	
			StandingsStack* bestThree = calculateTopThree(topthree);
			return bestThree;
		}
			
		else if (playerTwoSize == 0)
		{
			cout << p2->getTeamName() << " had no winners, therefore the winners are all those who won once belonging to the team " << p2->getTeamName() << endl;
		
			//int counter = 0;

			while (this->winners->checkEmpty() != true)
				{
					Creature* c1 = this->winners->dequeue();
					topthree->enqueue(c1);
					//counter++;
				}

			/*while (this->winners->checkEmpty() != true)
				{
					Creature* c1 = this->winners->dequeue();
					fullList->push(c1);
				}*/
			StandingsStack* bestThree = calculateTopThree(topthree);
					
			return bestThree;
		}

while (this->winners->returnSize() != 0 && p2->winners->returnSize() != 0)
{
		Creature* play1 = this->winners->dequeue(); // pop off the first creature from the queue
		Creature* play2 = p2->winners->dequeue();
		static int gameCounter = 1;

		cout << endl << "GAME " << gameCounter << ": " << play1->getName() << " of the " << this->getTeamName() << " vs. " << play2->getName() << " of the " << p2->getTeamName() << endl;

		int roundCounter = 1;	
		cout << play1->getSpecies() << " has " << play1->getStrengthPoints() << endl;
		cout << play2->getSpecies() << " has " << play2->getStrengthPoints() << endl;

		while (play1->getStrengthPoints() > 0 && play2->getStrengthPoints() > 0) // fight until one dies
		{

			cout << endl << "------ ROUND " << roundCounter << " ------" << endl;

		
			play1->attackCreature(play2);
			play2->attackCreature(play1);
			
			roundCounter++;	
		}

		if (play1->getStrengthPoints() == 0) // ASSUMES BOTH PLAYERS CANNOT DIE. If player1's creature dies, add that creature to the losers queue,
		// and add player2's creature to the winners queue
		{
			play2->regenHealth();
			//fullList->push(play1);
			if (topthree->search(play2) == false) // dont add it twice
				topthree->enqueue(play2);

			if (topthree->search(play1) == false)
				topthree->enqueue(play1);
			
			this->timesBeenKilledByEnemy++;
			p2->timesKilledEnemy++;
			p2->winners->enqueue(play2);
		}

		else if (play2->getStrengthPoints() == 0)
		{
			play1->regenHealth();
			//fullList->push(play2);
			
			if (topthree->search(play1) == false)
				topthree->enqueue(play1);

			if (topthree->search(play2) == false)
				topthree->enqueue(play2);

			this->winners->enqueue(play1);
			this->timesKilledEnemy++;
			p2->timesBeenKilledByEnemy++;
		}		

		gameCounter++;	

}

	StandingsStack* finalThree = calculateTopThree(topthree);
	return finalThree;

}

StandingsStack* Player::calculateTopThree(LineupQueue* top)
{
	// a character must have made it to the winner's bracket to be considered for top three. the top three creatures are based off number of kills

	LineupQueue* ordered = top->returnOrdered(); // returns large numbers first
	StandingsStack* finalThree = new StandingsStack;

	
	Creature* c1 = ordered->dequeue(); // largest kill count
	Creature* c2 = ordered->dequeue();
	Creature* c3 = ordered->dequeue(); // 3rd largest kiill count
	finalThree->push(c3);
	finalThree->push(c2);
	finalThree->push(c1);

	// Arrange the competitors past third place in order of highest kill count.
	
	int size = ordered->returnSize(); // sort this correctly. the first element to be pulled out is the smallest # of kills
	StandingsStack* temp = new StandingsStack;

	while (ordered->checkEmpty() == false)
	{	
		Creature* c4 = ordered->dequeue(); // dequeue from lowest to highest kill count
		temp->push(c4);
	}

	while (temp->isEmpty() == false)
	{
		Creature* c5 = temp->pop();
		fullList->push(c5);	// when popped, temp will go from highest to lowest kill count
	}
	
	return finalThree;		
}

void Player::printRoster()
{
	if (roster->first != NULL)
	{
		cout << "*****Team " << teamName << " has the roster: *****" << endl;
		roster->printQueue();
	}
}

void Player::printWinners()
{
	if (winners->first != NULL)
	{
		cout << "*****Team " << teamName << " have the winners: *****" << endl;	
		winners->printQueue();
	}
}

void Player::printLosers()
{
	if (losers->first != NULL)
	{
		cout << "*****Team " << teamName << " have the losers: *****" << endl;
		losers->printQueue();
	}
}	

string Player::getTeamName()
{
	return teamName;
}

void Player::printStack()
{
	fullList->printList();
}

void Player::printFinal(Player* p2)
{
	double player1Kills = this->timesKilledEnemy;
	double player1Deaths = this->timesBeenKilledByEnemy;
	double player2Kills = p2->timesKilledEnemy;
	double player2Deaths = p2->timesBeenKilledByEnemy;

	double player1Ratio;
	double player2Ratio;

	if (player1Deaths == 0)
		player1Ratio = player1Kills;

	else
		player1Ratio = player1Kills/player1Deaths;

	if (player2Deaths == 0)
		player2Ratio = player2Kills;

	else
		player2Ratio = player2Kills/player2Deaths;

	cout << endl << this->getTeamName() << " KILLS: " << player1Kills << endl;
	cout << this->getTeamName() << " DEATHS: " << player1Deaths << endl;
	cout << this->getTeamName() << " KILL DEATH RATIO: " << player1Ratio << endl;
	cout << endl << p2->getTeamName() << " KILLS: " << player2Kills << endl;
	cout << p2->getTeamName() << " DEATHS: " << player2Deaths << endl;
	cout << p2->getTeamName() << " KILL DEATH RATIO: " << player2Ratio << endl;

	if (player1Ratio < player2Ratio)
	cout << "Team " << p2->getTeamName() << " has won with a higher kill death ratio." << endl;
	
	else if (player1Ratio > player2Ratio)
	cout << "Team " << this->getTeamName() << " has won with a higher kill death ratio." << endl;

	else
	cout << "The two teams have tied with equal kill death ratios." << endl;
}
	
