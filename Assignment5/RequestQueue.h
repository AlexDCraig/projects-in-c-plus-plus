// requestqueue header file, used to act as a buffer

#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Requests.h"


class RequestQueue
{
private:
	class RequestNode
	{
		friend class RequestQueue;
		Requests* r1;
		RequestNode* next;
		RequestNode* previous;
		RequestNode(Requests* r, RequestNode* next1 = NULL, RequestNode* previous1 = NULL)
		{
			r1 = r;
			next = next1;
			previous = previous1;
		}
	};

	RequestNode* front;
	RequestNode* rear;

public:
	RequestQueue(int maxSize);
	~RequestQueue();
	void enqueue(Requests*);
	Requests* dequeue();
	bool isEmpty();
	void deleteAll();
	int max;
	int currentSize;
};

#endif	
