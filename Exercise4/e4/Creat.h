/* Program Filename: Creature.h
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Skeleton for the Creature class, the class that is the 
 * basis for all of the other classes.
 */

#ifndef CREAT_H
#define CREAT_H

#include <string>

using std::string;

class Creature // abstract base class, cannot be instantiated.
{
protected:
	int attack;
	int defense;
	int armor;
	int strengthPoints;
	string name;
	string species;
	string owner;

public:
	Creature();
	virtual int calculateAttack() = 0; // each subclass will calculate their attack on their own. This function needs to set the Attack.
	virtual int calculateDefense() = 0; // pure virtual function, not defined in base class. So inherited classes MUST define this function.
	virtual bool getHasPlayed() = 0;
	virtual int regenHealth() = 0;
	void attackCreature(Creature*);
	void setName(string); 
	void setSpecies(string);
	void setAttack(int);
	void setDefense(int);
	void setOwner(string);
	void setArmor(int);
	void setStrengthPoints(int);
	virtual void incrementTimesKilled() = 0;
	virtual void incrementTimesBeenKilled() = 0;
	virtual int getTimesKilled() = 0;
	virtual int getTimesBeenKilled() = 0;
	void printRecord();
	string getName();
	string getSpecies();
	int getAttack();
	int getDefense();
	string getOwner();
	int getArmor();
	int getStrengthPoints();
};

#endif
