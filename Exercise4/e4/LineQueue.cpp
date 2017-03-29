#include "LineQueue.h"
#include "Play.h"
#include "Creat.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// default constructor
LineupQueue::LineupQueue()
{
    first = NULL;
    last = NULL;
    //srand(time(0));
}

// destructor
LineupQueue::~LineupQueue()
{
    deleteAll();
}

// add a character pointer to the end of the queue
void LineupQueue::enqueue(Creature* character) // change
{
    if (checkEmpty() == true) // nothing in the queue
    {
        first = new QueueNode(character); // first now holds the first node
        last = first; // last is the first node
    }
    
    else
    {
        last->next = new QueueNode(character); // set the value after next to the character provided
        last = last->next; // last must move one spot backwards
    }
}

// pop the first character pointer that was entered into the queue out
Creature* LineupQueue::dequeue() // change
{
    QueueNode* placeholder; // for deletion purposes
    Creature* val; // to return the data deleted

            if (checkEmpty() == false)
        {
            val = first->character; // first structure in queue now holds the character
            placeholder = first; // to prepare the first structure for deletion
            first = first->next; // Move the first structure back one position
            delete placeholder; // delete where the first structure was
            return val; // return what the first structure was
        }
        
        else // if queue empty
        {
            cout << "The queue is empty." << endl;
            exit(1);
        }
}

// returns true if the queue's first pointer doesn't exist
bool LineupQueue::checkEmpty()
{
    if (first == NULL)
        return true;
        
    else
        return false;
}

// to be used for destructor
void LineupQueue::deleteAll()
{
    while (checkEmpty() == false)
        dequeue();
}

// print function
void LineupQueue::printQueue()
{
	QueueNode* place = first;

	while (place != NULL)
	{
		Creature* c1 = place->character;
		cout << c1->getName() << " the " << c1->getSpecies() << " of the team " << c1->getOwner() <<  endl;
		place = place->next;
	}
}

// get an idea of how many nodes currently exist in the queue
int LineupQueue::returnSize()
{
	QueueNode* place = first;
	int size = 0;

	while (place != NULL)
	{
		size++;
		place = place->next;
	}

	return size;
}

// returns true if the creature pointer toFind exists within the queue
bool LineupQueue::search(Creature* toFind)
{
	if (first == NULL)
		return false;

	else
	{
		QueueNode* place = first;
		
		while (place != NULL)
		{
			if (toFind->getName() == place->character->getName())
				return true;

			place = place->next;
		}

		return false;
	}
}

// uses an array to perform a bubblesort on the queue and then slides it into a new queue and returns it
LineupQueue* LineupQueue::returnOrdered() // returns queue ordered from highest to lowest, as in the enqueue will pop out a large number and then progressively smaller
{
	int initialSize = returnSize();
	Creature**  arr = new Creature*[initialSize];
	int counter = 0;	

	while (checkEmpty() == false)
	{
		arr[counter] = dequeue();
		counter++;
	}

	// bubblesort the winning creatures by kills -- least to greatest number

	for (int i = (initialSize - 1); i >= 0; i--)
	{
		for (int j = 1; j <= i; j++)
		{
			if ((arr[j - 1]->getTimesKilled()) > (arr[j]->getTimesKilled()))
			{
				Creature* temporary = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = temporary;
			}
		}
	}
	
	LineupQueue* orderedList = new LineupQueue;				
	
// put the sorted array into a new queue
//  recall queues are first in, first out- this means the largest # of kills will be last to go -- keep this in mind`:
	for (int k = initialSize - 1; k >= 0; k--)
		orderedList->enqueue(arr[k]);

	return orderedList;
}					
