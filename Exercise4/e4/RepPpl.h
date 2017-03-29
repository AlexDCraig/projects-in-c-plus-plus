/* Program Filename: ReptilePeople.h
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Skeleton for Reptile People class.
 */

#ifndef REPPPL_H
#define REPPPL_H

#include "Creat.h"

class ReptilePeople : public Creature
{
protected:
	static bool hasPlayed;
	int timesKilled;
	int timesBeenKilled;
public:
	ReptilePeople();
 	virtual int calculateAttack();
	virtual int regenHealth();
	virtual int calculateDefense();
	virtual bool getHasPlayed();
	virtual void incrementTimesKilled();
	virtual void incrementTimesBeenKilled();
	virtual int getTimesKilled();
	virtual int getTimesBeenKilled();
};

#endif
