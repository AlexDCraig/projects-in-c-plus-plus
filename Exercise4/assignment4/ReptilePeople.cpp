/* Program Filename: ReptilePeople.cpp
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Implementation of ReptilePeople class. 
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "ReptilePeople.h"
using namespace std;

ReptilePeople::ReptilePeople()
{
	armor = 7;
	strengthPoints = 18;
	name = "Reptile People";
	species = "Reptile People";
	//srand(time(0));
}

/* Function: calculateAttack
 * Description: calculates ReptilePeople's attack based on specs
 * Output: returns ReptilePeople's attack score
 */

int ReptilePeople:: calculateAttack()
{	
	hasPlayed = true; // now reptilePeople will be toggled	

	cout << endl << "The Reptile People will roll three 6-sided dice for their attack." << endl;
	int attack1 = rand() % 6 + 1; // generate num between 1, 6
	cout << "The Reptile People have rolled a " << attack1 << "." << endl;
	int attack2 = rand() % 6 + 1;
	cout << "On their second roll, the Reptile People got a " << attack2 << "." << endl;
	int attack3 = rand() % 6 + 1;
	cout << "On their third and final roll, they got a " << attack3 << "." << endl;
	int attackPts = attack1 + attack2 + attack3; // total attack pts is the sum of all three attacks
	setAttack(attackPts);
	return attackPts;
}

/* Function: calculateDefense
 * Description: calculates reptilepeoples attack based on specs
 * Output: returns reptilepeoples attack score
 */

int ReptilePeople:: calculateDefense()
{
	hasPlayed = true;

	cout << endl << "The Reptile People will roll one 6-sided die for their defense." << endl;
	int defense1 = rand() % 6 + 1;
	cout << "To defend themselves, the Reptile People's only roll was a " << defense1 << "." << endl;
	int defensePts = defense1;
	setDefense(defensePts);
	return defensePts;
}

int ReptilePeople::regenHealth()
{
	cout << endl << this->getName() << ", the ReptilePeople, will throw 1 die of 6 sides to determine how much health to regenerate." << endl;
	int regen = rand() % 6 + 1;
	int currentStrength = getStrengthPoints();
	setStrengthPoints(currentStrength + regen);
	cout << endl << "ReptilePeople's strength points have gone from " << currentStrength << " to " << getStrengthPoints() << endl;
}

bool ReptilePeople::getHasPlayed()
{
	return hasPlayed;
}

void ReptilePeople::incrementTimesKilled()
{
	timesKilled++;
}

void ReptilePeople::incrementTimesBeenKilled()
{
	timesBeenKilled++;
}

int ReptilePeople::getTimesKilled()
{
	return timesKilled;
}

int ReptilePeople::getTimesBeenKilled()
{
	return timesBeenKilled;
}
