// Struct: Card. Pointers to this struct will be used to handle the deck of cards.

#ifndef CARD_H
#define CARD_H

#include <string>
using std::string;

struct Card
{
	string suit;
	string rank;
};

#endif
