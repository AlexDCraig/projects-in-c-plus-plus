/* Program Filename: Hydra.h
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Implementation of Hydra class.
 */

#include "Hydra.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

Hydra::Hydra()
{
	armor = 3;
	strengthPoints = 12;
	specialAttack = false;
	name = "Hydra";
	species = "Hydra";
	//srand(time(0));
}

/* Function: calculateAttack
 * Description: Given Hydra's capabilities, this calculates her attack score. If her special attack has been activated, she gets an additional six sided die.
 * Output: returns the randomized value that represents Hydra's move
 */

int Hydra::calculateAttack()
{
	hasPlayed = true; // this variable is meant to control when the special attack is used. If the special attack is set to true, it should not change unless it hits this function
	
	if (getSpecialAttack() == true) // if the special attack has been activated
	{
		cout << endl << "SINCE THE HYDRA'S SPECIAL ATTACK HAS BEEN ACTIVATED, SHE WILL ROLL TWO 6-SIDED DICE!!!!" << endl;
		int attack1 = rand() % 6 + 1;
		int attack2 = rand() % 6 + 1;
		int attackPts = attack1 + attack2;
		cout << " The Hydra rolled two dice for a sum of  " << attackPts << "." << endl;		
		setAttack(attackPts);
		specialAttack = false; // cancel the special attack		
		return attackPts; 
	}

	else // no special attack
	{
		int attack1 = rand() % 6 + 1;
		cout << "The Hydra has rolled a " << attack1 << "." << endl;
		int attackPts = attack1;
		setAttack(attackPts);
		return attackPts;
	}
}

/* Function: calculateDefense
 * Description: calculates hydra's defensive roll given her abilities, the chance to get her special attack is available whenever she takes damage
 * Post-Conditions: returns the defense to be used in the game
 */

int Hydra::calculateDefense()
{
	hasPlayed = true;
	
	if (getSpecialAttack() == false)
	headSevered();

	int defense1 = rand() % 6 + 1;
	setDefense(defense1);
	return defense1;
}

/* Function: headSevered
 * Description: calculates the 10% chance that one of hydra's heads are severed, if it is severed, hydra's special attack will be enabled to be used on the next attack cycle
 */

void Hydra::headSevered()
{
	if (rand() % 100 < 10) // the hydra has a 10% shot of one of her heads getting cut off. usedAttack is false
		// because if the Hydra gets the attack but then is on defense again it should not forfeit the attack through another chance.
	{
		specialAttack = true;
		cout << endl << endl << "*****BUT WAIT!!! THE HYDRA HAS LOST ONE OF ITS HEADS WHILE TAKING DAMAGE. TWO NEW HEADS HAVE GROWN IN ITS PLACE. THE HYDRA HAS BEEN GIVEN AN ADDITIONAL"
			<< " SIX SIDED DIE FOR HER NEXT ATTACK.*****" << endl << endl;
	}

}

int Hydra::regenHealth()
{
	cout << endl << this->getName() << ", the Hydra, will throw 1 die of 6 sides to determine how much health to regenerate." << endl;
	int regen = rand() % 6 + 1;
	int currentStrength = getStrengthPoints();
	setStrengthPoints(currentStrength + regen);
	cout << endl << "Hydra's strength points have gone from " << currentStrength << " to " << getStrengthPoints() << endl;
}

bool Hydra::getSpecialAttack()
{
	return specialAttack;
}

void Hydra::incrementTimesKilled()
{
	timesKilled++;
}

void Hydra::incrementTimesBeenKilled()
{
	timesBeenKilled++;
}

int Hydra::getTimesKilled()
{
	return timesKilled;
}

int Hydra::getTimesBeenKilled()
{
	return timesBeenKilled;
}
bool Hydra::getHasPlayed()
{
	return hasPlayed;
}
