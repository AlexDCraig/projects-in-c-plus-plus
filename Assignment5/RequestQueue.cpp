// requestqueue implementation file
// this is a standard queue except it has a pointer to the previous node
// and has a maximum size that deletes off stuff automatically

#include "Requests.h"
#include "RequestQueue.h"
#include <iostream>
#include <cstdlib>
using namespace std;

RequestQueue::RequestQueue(int maximum)
{	
	front = NULL;
	rear = NULL;
	max = maximum;
	currentSize = 0;		
}

RequestQueue::~RequestQueue()
{
	deleteAll();
}	

void RequestQueue::enqueue(Requests* req)
{
	if (isEmpty() == true)
	{
		front = new RequestNode(req);
		rear = front;
	}

	else
	{
		RequestNode* temp = rear;
		rear->next = new RequestNode(req);
		rear = rear->next;
		rear->previous = temp;
	}
}	

Requests* RequestQueue::dequeue()
{
	RequestNode* temp;

	if (isEmpty() == true)
	{
		cout << "Empty queue." << endl;
		exit(1);
	}

	else
	{
		Requests* req = front->r1;
		temp = front;
		front = front->next;
		delete temp;
		return req;
	}
}

bool RequestQueue::isEmpty()
{
	if (front == NULL)
		return true;
	
	else
		return false;
}	

void RequestQueue::deleteAll()
{
	while (isEmpty() == false)
		dequeue();

}
