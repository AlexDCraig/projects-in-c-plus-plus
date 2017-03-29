/* Program Filename: Creature.cpp
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: implements creature, the base class for each other class
 * Note: Abstract class, has several pure functions.
 */

#include "Creat.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; using std::string;

Creature::Creature()
{
	name = "";
	species = "";
	attack = 0;
	defense = 0;
	armor = 0;
	strengthPoints = 0;
	owner = "";
	//srand(time(0));
}

/* Function: attackCreature
 * Description: The meat of the program. The caller is the attacker, takes a pointer
 * to Creature as a parameter, that is the defender.
 * Input: pointer to Creature
 */

void Creature::attackCreature(Creature* enemy) 
{	
	if (this->getStrengthPoints()  == 0) // recall strength is health
	{
		cout << this->getName() << ", the " << this->getSpecies() <<  ", has no strength points. " << 
		this ->getName() << " has lost the will to attack." << endl;
	}

	else if (enemy->getStrengthPoints() == 0)
	{
		cout << enemy->getName() << ", the " << enemy->getSpecies() << ",  has no strength points and cannot"
		<< " defend itself. " << endl;
	}

	else
	{
		cout << endl << this->getName() << ", the " << this->getSpecies() << ",  wants to attack " << enemy->getName() << ", the " << enemy->getSpecies() << 
		"!!!!!!" << endl;
		int attack = this->calculateAttack(); // the attacking creature's attack score, calculateAttack rolls dice and returns the value
		cout << this->getName() <<  " the " << this->getSpecies() << "'s ATTACK ROLL(S): " << attack << "." << endl;

		int defense = enemy->calculateDefense(); // the defensive creature's defense score, should roll dice and return that value
		cout << enemy->getName() << " the " << enemy->getSpecies() << "'s DEFENSE ROLL(S): " << defense << "." << endl;

		int damage = 0;
		bool defenseWon = false;

	// these are logic statements which cover the various conditions. 
	// ex: if defense is bigger than attack, then damage should not
	// be negative points (i.e. more health)
	
		if ((attack - defense) > 0) // valid option b/c damage will be positive, which it should be
	 		damage = attack - defense;

		else // enemy has rolled a good defensive dice score
		{
			cout << "The defense has beaten the attack." << endl;
			defenseWon = true;
		}
	
		if (defenseWon == false) // if the defensive roll hasn't stopped attack
		{	
			//cout << endl << "The initial damage: " << endl << "ATTACK: " << 		attack << "   DEFENSE: " << defense << endl;
			//cout << "Before armor rating comes into play, the damage is " << 		damage << " pts." << " to " << enemy->getName() << "'s strength.		" << endl << endl;

			int enemyArmor = enemy->getArmor();
		//cout << "However, " << enemy->getName() << " has an armor "   			<< "rating of " << enemyArmor << "." << endl;
	
			if ((damage - enemyArmor) >= 0) // damage should be either positive or 0, it shouldn't be negative
				damage  = damage - enemyArmor;

			else if ((damage - enemyArmor) < 0) // the smallest value damage can be is 0
			{
				damage = 0;
				cout << "The creature's armor has absorbed the attack." << endl;
			}
	

			int originalHealth = enemy->getStrengthPoints();
	
			if ((enemy->getStrengthPoints() - damage) > 0)
			// if the enemy has enough strength to withstand
			{	
				int newStrength = originalHealth - damage;
				enemy->setStrengthPoints(newStrength);
				cout << enemy->getName() << " the " << enemy->getSpecies() <<  "'s strength points have gone from " << originalHealth << " to "
				<< enemy->getStrengthPoints() << "." << endl;		
			}	

			else // if the enemy doesn't have enough strength
			{	
				int newStrength = 0;
				cout << enemy->getName() << " the " << enemy->getSpecies() << "  had " << originalHealth << " strength points. But it has taken that in damage. " << endl;
				enemy->setStrengthPoints(newStrength);
				cout << "The " << enemy->getName() << " of the team " << enemy->getOwner() << "  has been defeated. " << endl;
				enemy->incrementTimesBeenKilled();
				this->incrementTimesKilled();
			}
	}
   }	
}

void Creature::setAttack(int attack)
{
	this->attack = attack;
}

void Creature::setDefense(int defense)
{
	this->defense = defense;
}

void Creature::setArmor(int armor)
{
	this->armor = armor;
}

void Creature::setOwner(string p1)
{
	owner = p1;
}

void Creature::setSpecies(string spec)
{
	species = spec;
}

void Creature::setName(string nam)
{
	name = nam;
}

void Creature::setStrengthPoints(int strengthPoints)
{
	this->strengthPoints = strengthPoints;
}

// Uses polymorphism to print the Win-Loss record of each 
// subclass object that has engaged in battle.

void Creature::printRecord()
{
	cout << "**********" << name << "the " << species << "'s RECORD: **********" << endl;
	cout << "    NUMBER OF TIMES KILLED THE ENEMY: " << getTimesKilled() << ".";
	cout << endl << "    NUMBER OF TIMES BEEN KILLED: " << getTimesBeenKilled() 
	<< "." << endl;
}

string Creature::getName()
{
	return name;
}

string Creature::getOwner()
{
	return owner;
}

string Creature::getSpecies()
{
	return species;
}

int Creature::getAttack()
{
	return attack;
}

int Creature::getDefense()
{
	return defense;
}

int Creature::getArmor()
{
	return armor;
}

int Creature::getStrengthPoints()
{
	return strengthPoints;
}
