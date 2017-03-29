/* Program Filename: BlueMen.h
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Skeleton for the Blue Men class.
 */

#ifndef BLUE_H
#define BLUE_H

#include "Creat.h"

class BlueMen : public Creature
{
protected:
	static bool hasPlayed;
	int timesKilled;
	int timesBeenKilled;
public:
	BlueMen();
	virtual int calculateAttack();
	virtual int calculateDefense();
	virtual bool getHasPlayed();
	virtual void incrementTimesKilled();
	virtual void incrementTimesBeenKilled();
	virtual int regenHealth();
	virtual int getTimesKilled();
	virtual int getTimesBeenKilled();
};

#endif
