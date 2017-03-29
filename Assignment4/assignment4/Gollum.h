/* Program Filename: Gollum.h
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Skeleton for Gollum class.
 */

#ifndef GOLLUM_H
#define GOLLUM_H

#include "Creature.h"

class Gollum : public Creature
{
protected:
	static bool hasPlayed;
	int timesKilled;
	int timesBeenKilled;
public:
	Gollum();
	virtual int calculateAttack();
	virtual int calculateDefense();
	virtual int regenHealth();
	bool backJump();
	virtual bool getHasPlayed();
	virtual void incrementTimesKilled();
	virtual void incrementTimesBeenKilled();
	virtual int getTimesKilled();
	virtual int getTimesBeenKilled();
};

#endif
