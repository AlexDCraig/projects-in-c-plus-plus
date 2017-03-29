/* Program Filename: Gollum.cpp
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: implementation for gollum class, a weak derivative of creature that has a special attack
 */

#include "Gollum.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

Gollum::Gollum()
{
	armor = 3;
	strengthPoints = 8;
	name = "Gollum";
	species = "Gollum";
	//srand(time(0));
}

/* Function: calculateAttack
 * Description: calculate odds of special attack, if special attack is turned active, then print out a message indicating this and have the returned attack value reflect the added damage
 * Post-Conditions: returns int that corresponds to gollums attack score
 */

int Gollum::calculateAttack()
{
	hasPlayed = true;

	bool specialAttack = backJump(); // backJump calculates the odds of special attack

	if (specialAttack == true) // gollum gets 3 dice
	{
		cout << "*****WITH A 5% CHANCE OF OCCURRING, GOLLUM HAS UNLEASHED HIS SPECIAL ATTACK.*****" << endl;
		cout << "GOLLUM GETS TO ROLL THREE 6-SIDED DICE!!!" << endl;

		int attack1 = rand() % 6 + 1;
		int attack2 = rand() % 6 + 1;
		int attack3 = rand() % 6 + 1;
		int attackPts = attack1 + attack2 + attack3; // combine the two scores
		setAttack(attackPts);
		return attackPts;
	}

	else
	{
		cout << "Gollum rolls one 6-sided die. ";
		int attack1 = rand() % 6 + 1;
		int attackPts = attack1;
		setAttack(attackPts);
		return attackPts;
	}
}

/* Function: calculateDefense
 * Description: gollum gets to throw one 6-sided die, numbers 1-6 randomized, one number returned to correspond for his defensive score
 */

int Gollum::calculateDefense()
{
	hasPlayed = true;

	int defense1 = rand() % 6 + 1;
	cout << "Gollum has one roll for defense. ";
	int defensePts = defense1;
	setDefense(defensePts);
	return defensePts;
}

/* Function: backJump
 * Description: calculates 5% chance of special attack
 * Post-conditions: returns true if the number generated randomly is 0 - 4
 */

bool Gollum::backJump() // Gollum has a five percent chance of rolling three 6-sided dice- a special attack.
{
	bool backJump = false;

	if (rand() % 100 < 5) // Calculate a 5 percent chance. "<" 5 because it can generate the number 0, so "<=" would mean the numbers 0 - 5, which would 
		// be a 6% chance. 
	{
		backJump = true;
	}

	return backJump;
}

int Gollum::regenHealth()
{
	cout << endl << this->getName() << ", the Gollum, will throw 1 die of 6 sides to determine how much health to regenerate." << endl;
	int regen = rand() % 6 + 1;
	int currentStrength = getStrengthPoints();
	setStrengthPoints(currentStrength + regen);
	cout << endl << "Gollum's strength points have gone from " << currentStrength << " to " << getStrengthPoints() << endl;
}

bool Gollum::getHasPlayed()
{
	return hasPlayed;
}

void Gollum::incrementTimesKilled()
{
	timesKilled++;
}

void Gollum::incrementTimesBeenKilled()
{
	timesBeenKilled++;
}

int Gollum::getTimesKilled()
{
	return timesKilled;
}

int Gollum::getTimesBeenKilled()
{
	return timesBeenKilled;
}
