#include "RecursiveFibonacci.h"
#include <iostream>
using namespace std;

RecursiveFibonacci::RecursiveFibonacci()
{
}

RecursiveFibonacci::RecursiveFibonacci(int n)
{
	this->n = n;
	numSteps = 0;
}

RecursiveFibonacci::~RecursiveFibonacci()
{
}

int RecursiveFibonacci::Fibonacci(int n)
{
	if (n == 0)
		{
			numSteps++;
			return 0;
		}

	else if (n == 1)
		{
			numSteps++;
			return 1;
		}

	
	numSteps++;
	return Fibonacci(n - 1) + Fibonacci (n - 2);
}

void RecursiveFibonacci::print()
{
	int FibonacciNum = Fibonacci(n);
	cout << n << "th fibonacci number: " << FibonacciNum << endl;
	cout << "Number of steps required: " << numSteps << endl;
}	
