/*
********************************************************************
**Program Filename: war.cpp

**Author: Alex Hoffer

**Date: 10/2/2015

**Description: Establishes a class called Player that can play a modified
version of War, instantiates two Player objects and has them play. 
Prints out the record of the winner.

**Input: The user must enter how many rounds to play. This number is sent
to the static data member of the class for reference.

**Output: Prints out the winner, the loser, and the W-L records of both.

********************************************************************/

#include <iostream>
#include <cstdlib> // needed to use srand, rand
#include <ctime> // used to generate random number
#include <string>
using namespace std;

const int MAX_CARD_NUM = 52; // this is the highest number a player can generate

class Player
{
private:
	string identifier; 
	int numOfWins;
	static int numOfRounds; // the number of rounds should be shared between both players
	unsigned seedVal; // unsigned because it should be positive

public:
	Player();

	int genCardNum();

	void setStatic(int roundNum) // sets the static member
	{
		numOfRounds = roundNum;
	}

	int getStatic() const // returns the static member
	{
		return numOfRounds;
	}

	int getNumWins() const
	{
		return numOfWins;
	}

	void operator++() // make the ++ operator increment the object's win count
	{
		numOfWins++;
	}

	void playGame(Player&); 
};

int Player::numOfRounds = 0; // definition of static member outside of the class

/*
********************************************************************
**Function: Player()

**Description: default constructor that initializes all member values to 0/empty.
Creates a unique seed for the object that will be used to generate
random values.

********************************************************************/
Player::Player()
{
	identifier = "";
	numOfWins = 0;
	seedVal = time(0); // plants a first random number according to 0 seconds
	srand(seedVal); // uses first random number as a seed for the player's card generation
}

/*
********************************************************************
**Function: genCardNum()

**Description: Generates a random number to be used for comparison
between players.

**Post-Conditions: returns an int

********************************************************************/

int Player::genCardNum()
{
	int cardNum = rand() % MAX_CARD_NUM + 1; // generates a random #, the mod divides it by 52...
	// ... and then returns the remainder. This sets the limit between 0 and 51. The 1 is added
	// so that the possible interval becomes 1 and 52
	return cardNum;
}

/*
********************************************************************
**Function: playGame

**Description: Loops from 1 until the final round while generating 
random numbers for both players and comparing them. If the number is 
larger for one player than that player's wincount will increase.
Once all rounds have been played it prints the winner.

**Parameters: a reference to a Player object that is treated
as if they are Player 2.

**Pre-Conditions: There must be two player objects.

**Post-Conditions: Three possible scenarios exist- player one wins,
or player two wins, or both players tie. Each print something
different.

********************************************************************/

void Player::playGame(Player &player2)
{
	this->identifier = "Player One";
	player2.identifier = "Player Two";

	for (int count = 1; count <= numOfRounds; count++)
		{
			int cardOne = this->genCardNum();
			int cardTwo = player2.genCardNum();

			if (cardOne > cardTwo)
				this->numOfWins += 1;

			else if (cardTwo > cardOne)
				player2.numOfWins += 1;
		}

	if (this->numOfWins > player2.numOfWins)
		{
			cout << identifier << " has won. The scoring breakdown is as follows: " << endl;
			cout << identifier << ": " << numOfWins << " wins out of " << numOfRounds << " rounds.\n";
			cout << player2.identifier << " only had " << player2.numOfWins << " wins.\n";
		}

	else if (player2.numOfWins > this->numOfWins)
		{
			cout << player2.identifier << " has won. The scoring breakdown is as follows: " << endl;
			cout << player2.identifier << ": " << player2.numOfWins << " wins out of " << player2.numOfRounds << " rounds.\n";
			cout << identifier << " only had " << numOfWins << " wins.\n";
		}

	else
			cout << "Both players have tied at " << this->numOfWins << " wins.\n";
}


int main()
{
	Player p1, p2;
	
	cout << "How many rounds would you like to play? " << endl;
	
	int userInput;
	cin >> userInput;
	p1.setStatic(userInput);
	
	p1.playGame(p2);

	return 0;
}