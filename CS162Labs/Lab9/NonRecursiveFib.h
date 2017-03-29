#ifndef NONRECURSIVEFIB_H
#define NONRECURSIVEFIB_H

class NonRecursiveFib
{
private:
	int n;
	int numSteps;

public:
	NonRecursiveFib(int n);
	void print();
	int Fibonacci(int n);
};

#endif
