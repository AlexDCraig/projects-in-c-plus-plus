/* Program Filename: Hydra.h
 * Author: Alex Hoffer
 * Date: 10/31/2015
 * Description: Skeleton for Hydra class.
 */

#ifndef HY_H
#define HY_H

#include "Creat.h"

class Hydra : public Creature
{
private:
	bool specialAttack;
protected:
	static bool hasPlayed;
	int timesKilled;
	int timesBeenKilled;
public:
	Hydra();
	virtual int calculateAttack();
	virtual int calculateDefense();
	virtual int regenHealth();
	void headSevered();
	bool getSpecialAttack();
	virtual bool getHasPlayed();
	virtual void incrementTimesKilled();
	virtual void incrementTimesBeenKilled();
	virtual int getTimesKilled();
	virtual int getTimesBeenKilled();
};

#endif
