#include "NonRecursiveFib.h"
#include <iostream>
using namespace std;

NonRecursiveFib::NonRecursiveFib(int n)
{
	this->n = n;
	numSteps = 0;
}

void NonRecursiveFib::print()
{
	int result = Fibonacci(n);
	cout << n << "th Fibonacci number: " << result << endl;
	cout << "Number of steps: " << numSteps << "." << endl;

}

int NonRecursiveFib::Fibonacci(int n)
{
	int first = 0;
	int second = 1;
	int counter = 2;

	while (counter < n)
	{
		int temp = second;
		second = first + second;
		first = temp;
		counter++;
		numSteps++;
	}

	if (n == 0)
		return 0;

	else
		return first + second;
}	




