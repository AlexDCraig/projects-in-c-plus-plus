// complexity : O(n^2)


using namespace std;
#include <iostream>
#include <fstream>
#include <cstdlib>


int minimumPosition(int[], int, int, int&);
void swap(int[], int, int);


int selectSort(int a[], int size)
{
	int steps = 0;

	for (int i = 0; i < size - 1; i++)
	{	
		int minPos = minimumPosition(a, size, i, steps);
		swap(a, minPos, i);
	}

	cout << "Sorted version: " << endl;

	for (int k = 0; k < size; k++)
	cout << a[k] << endl;

	return steps;
}

int minimumPosition(int a[], int size, int from, int& steps)
{
	int minPos = from;
	for (int i = from + 1; i < size; i++)
	{	
		steps++;
		if(a[i] < a[minPos])
		minPos = i;
	}

	return minPos;
}

void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

int main()
{
	// 1. Test unsorted (random)
	cout << "Testing selectionSort: Numbers in Random Order." << endl;
	ifstream read("randomorder");
	int i = 0;
	int n;
	int toRandomize[25];
	cout << "Before algorithm: " << endl;
	while (read>>n)
	{
		toRandomize[i] = n;
		cout << n << endl;
		i++;
	}
	 cout << endl << "Steps required: " << selectSort(toRandomize, 25);	



	// 2. Test reverse sorted
	cout << endl << "Testing selectionSort: Numbers sorted in reverse." << endl;
	ifstream read1("reversesorted");
	i = 0;
	n = 0;
	int toReverse[25];
	cout << "Before algorithm: " << endl;
	while (read1>>n)
	{
		toReverse[i] = n;
		cout << n << endl;
		i++;
	}

	cout << endl << "Steps required: " << selectSort(toReverse, 25);

	// 3. Test already sorted
	cout << endl << "Testing selection sort: Numbers already in Order." << endl;
	ifstream read2("sortedorder");
	i = 0;
	int toSorted[25];
	cout << "Before algorithm: " << endl;
	while (read2>>n)
	{
		toSorted[i] = n;
		cout << n << endl;
		i++;
	}

	cout << endl << "Steps required: " << selectSort(toSorted, 25);	





	return 0;

}




	
