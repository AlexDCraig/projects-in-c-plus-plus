#ifndef RECURSIVEFIBONACCI_H
#define RECURSIVEFIBONACCI_H

class RecursiveFibonacci
{
public:
	RecursiveFibonacci(int n);
	RecursiveFibonacci();
	~RecursiveFibonacci();
	int Fibonacci(int n);
	int numSteps;
	void print();

private:
	int n;
};

#endif		
