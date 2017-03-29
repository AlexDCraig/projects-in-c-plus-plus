#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>


using namespace std;


/* Helper function for finding the max of two numbers */
int max(int x, int y)
{
    if(x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

/* left is the index of the leftmost element of the subarray; right is one
 *  * past the index of the rightmost element */
void merge_helper(int *input, int left, int right, int *scratch, int& steps)
{
    /* base case: one element */
    if(right == left + 1)
    {
        return;
    }
    else
    {
        int i = 0;
        int length = right - left;
        int midpoint_distance = length/2;
        /* l and r are to the positions in the left and right subarrays */
        int l = left, r = left + midpoint_distance;

        /* sort each subarray */
        merge_helper(input, left, left + midpoint_distance, scratch, steps);
        merge_helper(input, left + midpoint_distance, right, scratch, steps);

        /* merge the arrays together using scratch for temporary storage */ 
        for(i = 0; i < length; i++)
        {
            /* Check to see if any elements remain in the left array; if so,
 *              * we check if there are any elements left in the right array; if
 *                           * so, we compare them.  Otherwise, we know that the merge must
 *                                        * use take the element from the left array */
            steps++;
		
		if(l < left + midpoint_distance && 
                    (r == right || max(input[l], input[r]) == input[l]))
            {
                scratch[i] = input[l];
                l++;
            }
            else
            {
                scratch[i] = input[r];
                r++;
            }
        }
        /* Copy the sorted subarray back to the input */
        for(i = left; i < right; i++)
        {
            input[i] = scratch[i - left];
		steps++;
        }
    }
}

/* mergesort returns true on success.  Note that in C++, you could also
 *  * replace malloc with new and if memory allocation fails, an exception will
 *   * be thrown.  If we don't allocate a scratch array here, what happens? 
 *    *
 *     * Elements are sorted in reverse order -- greatest to least */

int mergesort(int *input, int size)
{
    int steps = 0;
    int *scratch = (int *)malloc(size * sizeof(int));
    if(scratch != NULL)
    {
        merge_helper(input, 0, size, scratch, steps);
        free(scratch);
    }

	cout << "After sort: " << endl;

 	for (int i = 0; i < size; i++)
		cout << input[i] << endl;
	
	return steps;
}

int main()
{	
	// 1. Test unsorted (random)
	cout << "Testing mergesort: Numbers in Random Order." << endl;
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
	 cout << "Steps required: " << mergesort(toRandomize, 25);	



	// 2. Test reverse sorted
	cout << endl << "Testing mergesort: Numbers sorted in reverse." << endl;
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

	cout << endl << "Steps required: " << mergesort(toReverse, 25);

	// 3. Test already sorted
	cout << endl << "Testing mergesort: Numbers already in Order." << endl;
	ifstream read2("sortedorder");
	i = 0;
	int toSorted[25];
	while (read2>>n)
	{
		toSorted[i] = n;
		cout << n << endl;
		i++;
	}

	cout << endl << "Steps required: " << mergesort(toSorted, 25);	

	
	return 0;
}
