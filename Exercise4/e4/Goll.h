/* Program Filename: Gollum.h
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Skeleton for Gollum class.
 */

#ifndef GOLL_H
#define GOLL_H

#include "Creat.h"

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
