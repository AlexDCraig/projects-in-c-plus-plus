#include "RecursiveFibonacci.h"
#include "NonRecursiveFib.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "Let's find Fib. number of 10 using a recursive algorithm." << endl;
	int n= 10;
	RecursiveFibonacci r1(n);
	r1.print();
	NonRecursiveFib n1(n);
	cout << "Let's find Fib. number of 10 using an iterative algorithm." << endl;
	n1.print();
	return 0;
}
		
