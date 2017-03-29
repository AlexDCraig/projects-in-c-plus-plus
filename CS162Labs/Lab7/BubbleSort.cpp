// best: already in order. O(n^2)
// worst: reversed. O(n^2)
// average: O(n^2)
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>


using namespace std;


int bubbleSort(int a[], int size)
{
	int steps = 0;

	 for (int i = (size - 1); i >= 0; i--)
	{

		for (int j = 1; j <= i; j++)
		{	
			steps++;
			if (a[j-1] > a[j]) {
			// swap elements j-1 and j
			int temp = a[j-1];
			a[j-1] = a[j];
			a[j] = temp;
			}

			
		}
		
	}

	for (int k = 0; k < size; k++)
	cout << a[k] << endl;

	return steps;
}

int main()
{	
	// 1. Test unsorted (random)
	cout << "Testing Bubble Sort: Numbers in Random Order." << endl;
	ifstream read("randomorder");
	int i = 0;
	int n;
	int toRandomize[25];
	while (read>>n)
	{
		toRandomize[i] = n;
		cout << n << endl;
		i++;
	}
	 cout << "Steps required: " << bubbleSort(toRandomize, 25);	



	// 2. Test reverse sorted
	cout << endl << "Testing Bubble Sort: Numbers sorted in reverse." << endl;
	ifstream read1("reversesorted");
	i = 0;
	n = 0;
	int toReverse[25];
	while (read1>>n)
	{
		toReverse[i] = n;
		cout << n << endl;
		i++;
	}

	cout << endl << "Steps required: " << bubbleSort(toReverse, 25);

	// 3. Test already sorted
	cout << endl << "Testing Bubble Sort: Numbers already in Order." << endl;
	ifstream read2("sortedorder");
	i = 0;
	int toSorted[25];
	while (read2>>n)
	{
		toSorted[i] = n;
		cout << n << endl;
		i++;
	}

	cout << endl << "Steps required: " << bubbleSort(toSorted, 25);	


	return 0;
}	















		
		
	
				
 
