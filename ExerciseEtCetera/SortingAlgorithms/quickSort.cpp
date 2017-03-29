// Best case - scrambled, O(n log n)
// Worst case - already sorted, O(n^2)
// Average case - random pivot, O(n^2)

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

int quickSort(int arr[], int left, int right, int &steps) {


     int i = left, j = right;

      int tmp;

      int pivot = arr[(left + right) / 2];

 
      /* partition */

      while (i <= j) {

		steps++;

            while (arr[i] < pivot)
		{
	          steps++;
                  i++;
		
		}

            while (arr[j] > pivot)
	{
		steps++;         
         	j--;
		
	}	
	
            if (i <= j) {

                  tmp = arr[i];

                  arr[i] = arr[j];

                  arr[j] = tmp;

                  i++;

                  j--;
	
	          steps++;

            }

      };

 

      /* recursion */

      if (left < j)
           {
		 quickSort(arr, left, j, steps);
	   }
      if (i < right)
           {
		 quickSort(arr, i, right, steps);
	   }


	return steps;
}

int main()
{
	// 1. Test unsorted (random)
	cout << "Testing quickSort: Numbers in Random Order." << endl;
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
	int steps = 0;
	cout << endl << "Steps required: " << quickSort(toRandomize, 0, 25, steps);	



	// 2. Test reverse sorted
	cout << endl << "Testing quickSort: Numbers sorted in reverse." << endl;
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
	steps = 0;
	cout << endl << "Steps required: " << quickSort(toReverse, 0, 25, steps);

	// 3. Test already sorted
	cout << endl << "Testing quicksort: Numbers already in Order." << endl;
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
	steps = 0;
	cout << endl << "Steps required: " << quickSort(toSorted, 0, 25, steps);	


	return 0;
}
