/************ 
 * Class: LineupQueue
 * Description: a Queue data structure used to hold Creature pointers.
 * Will be used in conjunction with the StandingsStack to implement correct
 * storage procedures.
 */

#ifndef LINEUPQUEUE_H
#define LINEUPQUEUE_H

#include "Creature.h"
#include <iostream>
using namespace std;

class LineupQueue
{
private:
	friend class Player;
	class QueueNode
	{
        	friend class LineupQueue;
        	Creature* character; // change to creature
        	QueueNode* next;
        	QueueNode(Creature* c1, QueueNode* val = NULL) // change first parameter to creature
        	{
            		character = c1; // change
            		next = val;
        	}
    	};
    
    QueueNode* first; // tracks the front of the queue
    QueueNode* last; // tracks the end of the queue
    
public:
    LineupQueue();
    ~LineupQueue();
    void enqueue(Creature*); // change argument to creature
    Creature* dequeue(); // get rid of first creature, return that creature
    void deleteAll(); // contained as separate function so that the queue can be deleted outside of the destructor
    bool checkEmpty();
    void printQueue();
    int returnSize();
    LineupQueue* returnOrdered();
    bool search(Creature*);
};

#endif


