// Implementation of the Hand class.

#include "Hand.h"
#include "Card.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

// To be used with the sorting function below. Convert the rank from string to int and compare them.
bool stringComparison(Card* c1, Card* c2)
{
	string firstNumber = c1->rank;
	string secondNumber = c2->rank;
	int firstNum, secondNum;
	stringstream stringer(firstNumber);
	stringer >> firstNum;
	stringer.clear();
	stringer.str(secondNumber);
	stringer >> secondNum;

	if (firstNum < secondNum) // keep first num where its at
		return true;
	else if (firstNum >= secondNum) // put first num after secondnum
		return false;
}

// To be used with the sorting function below. Assign weighted values to the royal cards and sort them
// using these values.
bool royaltyComparison(Card* c1, Card* c2)
{
	string firstName = c1->rank;
	string secondName = c2->rank;
	int firstScore = 0;
	int secondScore = 0;
	
	if (firstName == "ace")	
		firstScore = 1;

	else if (firstName == "jack")
		firstScore = 2;

	else if (firstName == "queen")	
		firstScore = 3;

	else if (firstName == "king")
		firstScore = 4;

	if (secondName == "ace")
		secondScore = 1;

	else if (secondName == "jack")
		secondScore = 2;

	else if (secondName == "queen")
		secondScore = 3;

	else if (secondName == "king")
		secondScore = 4;

	if (firstScore < secondScore)
		return true;  // the first card passed is less than the second

	else if (firstScore >= secondScore)
		return false;		
	
}

Hand::Hand()
{
	handSize = 0;
}

// Add the pointer to the card struct to the vector that is a member of the hand class
void Hand::addToHand(Card* c1)
{
	cards.push_back(c1);
}

// get the pointer to the card,search through the cards vector and find it and erase it
Card* Hand::removeFromHand(Card* c1)
{
	for (int k = 0; k < cards.size(); k++) // search for the card
	{
		Card* c2 = cards.at(k);

		if (c2->rank == c1->rank && c2->suit == c1->suit)
		{
			cards.erase(cards.begin() + k); // remove card
			return c2; // return card
		}
	}
}

int Hand::getHandSize()
{
	handSize = cards.size();
	return handSize;
}

// uses the helper functions defined at the top to sort the hand into logical order
// the order goes: 2-10, ace, jack, queen, king
void Hand::sortHand() // sorts the hand by rank
{	
	vector <Card*> cardNumbers;
	vector <Card*> royaltyCards;
	string cardNum[10] = { "2", "3", "4", "5", "6", "7", "8", "9", "10" };
	string royalty[4] = { "ace", "jack", "queen", "king" };

	for (int k = 0; k < cards.size(); k++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (cards.at(k)->rank == cardNum[j])
			{
				cardNumbers.push_back(cards.at(k));
			}
		}
	}

	for (int k = 0; k < cards.size(); k++)
	{
		for (int r = 0; r < 4; r++)
		{
			if (cards.at(k)->rank == royalty[r])
			{
				royaltyCards.push_back(cards.at(k));
			}
		}
	}			

	// bubble sort the cardNumbers
	
	for (int q = cardNumbers.size() - 1; q >= 0; q--)
	{
		for (int j = 1; j <= q; j++)
		{
			if (stringComparison(cardNumbers.at(j - 1), cardNumbers.at(j)) == false) // if preceding element is greater than or equal to next el
			{
				Card* temporary = cardNumbers.at(j - 1);
				cardNumbers.at(j - 1) = cardNumbers.at(j);
				cardNumbers.at(j) = temporary;	
			}		
		}
	}

	// bubblesort the royals

	for (int n = royaltyCards.size() - 1; n >= 0; n--)
	{
		for (int k = 1; k <= n; k++)
		{
			if ((royaltyComparison(royaltyCards.at(k - 1), royaltyCards.at(k))) == false)
			{
				Card* temp = royaltyCards.at(k - 1);
				royaltyCards.at(k - 1) = royaltyCards.at(k);
				royaltyCards.at(k) = temp;
			}
		}
	}	
						
	cards.clear();

	for (int r = 0; r < cardNumbers.size(); r++)
	{
		cards.push_back(cardNumbers.at(r));
	}

	for (int v = 0; v < royaltyCards.size(); v++)
	{
		cards.push_back(royaltyCards.at(v));
	}

}	

// searches through the cards vector to see if they have the pointer described
bool Hand::hasCard(Card* ca)
{
	bool has = false;

	for (int r = 0; r < cards.size(); r++)
	{
		if (cards.at(r)->rank == ca->rank)
			has = true;
	}

	return has;
}
		



