/* Program Filename: Bluemen.cpp
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Implemention of blue men, the high powered derivative of creature
 */

#include "Blue.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

BlueMen::BlueMen()
{
	armor = 3;
	strengthPoints = 12;
	name = "Blue Men";
	species = "Blue Men";
	//srand(time(0));
}

/* Function: calculateAttack
 * Description: randomizes two numbers 1-10 adds them together returns the value to be bluemens attack score
 */

int BlueMen::calculateAttack()
{
	hasPlayed = true;
	cout << endl << "The Blue Men will roll two 10-sided dice for their attack." << endl;
	int attack1 = rand() % 10 + 1; // because the blue men is rolling a 10-sided die
	cout << "The Blue Men have rolled a " << attack1 << "." << endl;
	int attack2 = rand() % 10 + 1; // because the blue men gets to roll 2 dice
	cout << "On their second roll, the Blue Men got a " << attack2 << "." << endl;
	int attackPts = attack1 + attack2; // combine the two scores
	setAttack(attackPts);
	return attackPts;
}

/* Function: calculateDefense
 * Description: randomize three numbers 1-6, add them, return value to be bluemens defense score
 */

int BlueMen::calculateDefense()
{
	hasPlayed = true;
	cout << endl << "The Blue Men will roll three 6-sided dice for their defense." << endl;
	int defense1 = rand() % 6 + 1; // blue men rolls 6 sided die thrice for defense
	cout << "To defend themselves, the Blue Men's first roll is a " << defense1 << "." << endl;
	int defense2 = rand() % 6 + 1;
	cout << "Their second roll yielded a " << defense2 << "." << endl;
	int defense3 = rand() % 6 + 1;
	cout << "Their third roll brought a " << defense3 << "." << endl;
	int defensePts = defense1 + defense2 + defense3;
	setDefense(defensePts);
	return defensePts;
}

int BlueMen::regenHealth()
{
	cout << endl << "BlueMen will throw 1 die of 12 sides to determine how much health to regenerate." << endl;
	int regen = rand() % 12 + 1;
	int currentStrength = getStrengthPoints();
	setStrengthPoints(currentStrength + regen);
	cout << endl << "BlueMen's strength points have gone from " << currentStrength << " to " << getStrengthPoints() << endl;
}

bool BlueMen::getHasPlayed()
{
	return hasPlayed;
}

void BlueMen::incrementTimesKilled()
{
	timesKilled++;
}

void BlueMen::incrementTimesBeenKilled()
{
	timesBeenKilled++;
}

int BlueMen::getTimesKilled()
{
	return timesKilled;
}

int BlueMen::getTimesBeenKilled()
{
	return timesBeenKilled;
}
