/* Program Filename: Barbarian.cpp
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Lays out the Barbarian class implementation.
 * Output: Returns attack value, defense value.
 */

#include "Barb.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

Barbarian::Barbarian()
{
	armor = 0;
	strengthPoints = 12;
	name = "Barbarian";
	species = "Barbarian";
	//srand(time(0));
}

/* Function: calculateAttack
 * Description: randomizes number between 1 and 6 twice, sums them
 * Pre-Conditions: Should be used in battle
 */

int Barbarian::calculateAttack()
{
	hasPlayed = true;
	cout << endl << "The Barbarian will roll two 6-sided dice for his attack." << endl;
	int attack1 = rand() % 6 + 1; // because the barbarian is rolling a 6-sided die
	cout << "The Barbarian has rolled a " << attack1 << "." << endl;
	int attack2 = rand() % 6 + 1; // because the barbarian gets to roll 2 dice
	cout << "On his second roll, the Barbarian got a " << attack2 << "." << endl;
	int attackPts = attack1 + attack2; // combine the two scores
	setAttack(attackPts);
	return attackPts;
}

/* Function: calculateDefense
 * Description: randomizes number between 1 and 6 twice, sums them
 * Pre-Conditions: Should be used in battle
 */

int Barbarian::calculateDefense()
{
	hasPlayed = true;
	cout << endl << "The Barbarian will roll two 6-sided dice for his defense." << endl;
	int defense1 = rand() % 6 + 1; // barbarian rolls 6 sided die twice for defense
	cout << "To defend himself, the Barbarian's first roll is a " << defense1 << "." << endl;
	int defense2 = rand() % 6 + 1;
	cout << "His second roll yielded a " << defense2 << "." << endl;
	int defensePts = defense1 + defense2;
	setDefense(defensePts);
	return defensePts;
}

int Barbarian::regenHealth()
{
	cout << endl << this->getName() << ", the Barbarian, will throw 1 die of 6 sides to determine how much health to regenerate." << endl;
	int regen = rand() % 6 + 1;
	int currentStrength = getStrengthPoints();
	setStrengthPoints(currentStrength + regen);
	cout << endl << "Barbarian's strength points have gone from " << currentStrength << " to " << getStrengthPoints() << endl;
}

// these functions are essentially get and set functions

void Barbarian::incrementTimesKilled()
{
	timesKilled++;
}

void Barbarian::incrementTimesBeenKilled()
{
	timesBeenKilled++;
}

int Barbarian::getTimesKilled()
{
	return timesKilled;
}

int Barbarian::getTimesBeenKilled()
{
	return timesBeenKilled;
}	

bool Barbarian::getHasPlayed()
{
	return hasPlayed;
} 
