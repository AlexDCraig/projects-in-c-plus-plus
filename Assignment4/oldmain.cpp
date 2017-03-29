/* Program Filename: main
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: three functions, playgame, int main, and askUser combine to randomize characters at battle, simulate their attacks/defenses, and track their progress
 */

#include "Creature.h"
#include "BlueMen.h"
#include "Barbarian.h"
#include "Gollum.h"
#include "Hydra.h"
#include "ReptilePeople.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

void playGame();
void askUser(Creature**);


int main()
{
	srand(time(0)); // random number seeded to time(0)
	
	playGame();	

	return 0;
}

/* Function: playGame
 * Description: get an array of all possible subclasses, randomize which two are at battle, decide who goes first, let both attack and defend until death or # of rounds reached, pass off control to askUser function.
 * Post-Conditions: each array must be proper
 */

void playGame()
{
	Creature* array[5] = // all possible subclasses
	{
		new Gollum,
		new Barbarian,
		new ReptilePeople,
		new BlueMen,
		new Hydra
	};

	int firstPlayer = rand() % 5; // will be the first subclass randomly selected
	int secondPlayer = rand() % 5; //second subclass randomly selected

	 // the two players are allowed to be the same subclass

	cout << "First, we must establish two random combatants from the list of 5 subclasses. " << endl;
	cout << "The first creature randomly selected is a " << array[firstPlayer]->getName() << "." << endl;
	cout << "The second creature randomly selected is a " << array[secondPlayer]->getName() << "." << endl;
	
	int firstAttacker;
	int firstDefender;

	cout << "To determine who attacks first and who defends first, I will flip a fair coin. Heads means " << array[firstPlayer]->getName() << " attacks first, tails means " << array[secondPlayer]->getName() << " attacks first." << endl;

	int chance = rand() % 100;

	if (chance < 50) // corresponds to "Heads"
	{
		firstAttacker = firstPlayer;
		firstDefender = secondPlayer;
		cout << "I have flipped a heads." << endl;
	}

	else if (chance >= 50)
	{
		firstAttacker = secondPlayer;
		firstDefender = firstPlayer;
		cout << "I have flipped a tails." << endl;
	}

	string firstToAttack = array[firstAttacker]->getName();
	string firstToDefend = array[firstDefender]->getName();

	cout << "Therefore, the creature that gets to attack first is " << firstToAttack << "." << endl;
	cout << "The creature that must start out defending is " << firstToDefend << "." << endl;

 	cout << "How many rounds should we let these creatures battle?" << endl; 	int roundNum;
	cin >> roundNum;

	if (roundNum <= 0)
	{
		cout << "ERROR: Invalid information. Exiting game." << endl;
		exit(1);
	}

	cout << "Okay. We will let these creatures battle for " << roundNum << " rounds or until one perishes, whichever comes first." << endl;

	for (int k = 1; k <= roundNum && array[firstAttacker]->getStrengthPoints() != 0 && array[firstDefender]->getStrengthPoints() != 0; k++) // let it run for 10 rds or death
	{
		cout << endl << "**********ROUND " << k << "**********" << endl;
		array[firstAttacker]->attackCreature(array[firstDefender]);
		array[firstDefender]->attackCreature(array[firstAttacker]);
	}

	askUser(array);
	
}

/* Function: askUser
 * Description: Grabs the array, offers several options to the user visa vie the conclusion of the game they're playing.
 * Pre-Conditions: the Creature* array must be valid
 */

void askUser(Creature** array) // ** because it's an array of pointers to Creature
{
	cout << "Would you like to play again, with two different randomly selected creatures? Enter 1 for yes, 0 for no." << endl;
	int num;
	cin >> num;

	if (num == 1)
	{
		cout << "Would you like to print out the Win/Loss records of the creature types that have battled? 1 for yes, 0 for no." << endl;

		int input;
		cin >> input;
		
		if (input == 0)
		{
			cout << "Returning to beginning." << endl;
			playGame();
		}

		if (input == 1)
		{
			// print out win-loss records if creature has played
			for (int k = 0; k < 5; k++)
			{
				if (array[k]->getHasPlayed() == true)
				{	
					cout << endl;
					array[k]->printRecord();
					cout << endl;
				}
			}
			cout << "Great. Let's return back to the beginning now." << endl;
			playGame();
		}

		else
		{
			cout << "ERROR: Invalid number. Returning to beginning of game by default." << endl;
			playGame();
		}
	}

	else if (num == 0)
	{
		cout << "Thanks for playing." << endl;
		exit(0);
	}

	else
	{
		cout << "ERROR: Invalid number. Program exiting by default." << endl;
		exit(0);
	}
	
}








