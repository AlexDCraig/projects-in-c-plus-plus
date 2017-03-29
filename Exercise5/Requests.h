// To be used in the buffer to hold information about game history

#ifndef REQUESTS_H
#define REQUESTS_H

#include <string>
using namespace std;

struct Requests
{
	string asker; // player that asked
	int askerNumber;
	string haver;
	string suit;	// what that player asked for
	string rank;
	bool success;
};	

#endif
