/********************************************************************
**Program Filename: matrix.cpp

**Author: Alex Hoffer

**Date: 10/2/2015

**Description: uses nested for loops to transcribe two two-dimensional arrays, passes these
arrays along with an empty result array to a function which uses a for loop
to calculate the product of these arrays (treated like matrix multiplication).
The rows and columns that comprise the product are stored in the empty result
array. Back in main all three arrays are printed to look like matrices.

**Input: receives two two-dimensional arrays (one 2x3, the other 3x2).

**Output: prints out both 2D arrays in matrix form and also the product matrix of
these arrays.

********************************************************************/

#include <iostream>
#include <iomanip> // to manipulate the format of the output
using namespace std;

/*
********************************************************************
**Function: createMatrices

**Description: asks the user for values to fill in two matrices

**Parameters: two empty matrices, one 2x3, one 3x2 (in that order)

********************************************************************/

void createMatrices(double firstArray[2][3], double secondArray[3][2])
{
	cout << "Please impute six numbers to be entered into a first array. Press ENTER after each number.\n";

	for (int numRows = 0; numRows < 2; numRows++) // nested loop, fill in row 1's 3 columns, then fill in row 2's
	{
		for (int numCols = 0; numCols < 3; numCols++)
			cin >> firstArray[numRows][numCols];
	}

	cout << endl << "Now please enter six numbers for the second array.\n";

	for (int numRows = 0; numRows < 3; numRows++) // same as above just switch row and col numbers
	{
		for (int numCols = 0; numCols < 2; numCols++)
			cin >> secondArray[numRows][numCols];
	}

}

/*
********************************************************************
**Function: matrixMultiply

**Description: Accepts three 2-D arrays of doubles. First for loop calculates
dot products of rows and columns and stores them in variables, second
for loop moves these variables into the proper position in the result
matrix.

**Parameters: Three 2-D arrays of doubles- the first two are of compatible size
(2 x 3 and 3 x 2) to be multiplied such as matrices. The third is passed as
empty and is filled within the function.

**Pre-Conditions: Each array must be of double, the first array must consist
of 2 rows and 3 columns, the second array must consist of 3 rows and 2 columns,
and the third must consist of 2 rows and 2 columns. They must be this way
because matrix multiplication requires that the dimensions of the
arrays are n x m and m x n.

**Post-Conditions: The result matrix must hold the dot products
of the rows and columns of the first and second matrices.

********************************************************************/

void matrixMultiply(double firstArray[2][3], double secondArray[3][2], double result[2][2])
{
	double r1c1 = 0, r1c2 = 0, r2c1 = 0, r2c2 = 0; // these correspond to the result matrix: r = row, c = column

	for (int k = 0; k < 3; k++)
	{
		r1c1 += firstArray[0][k] * secondArray[k][0];
		// r1c1 of result matrix is the sum of 1st array's whole first row * 2nd array's whole first column
		// each successive calculation follows this pattern, just with diff. col/row

		r1c2 += firstArray[0][k] * secondArray[k][1];
		r2c1 += firstArray[1][k] * secondArray[k][0];
		r2c2 += firstArray[1][k] * secondArray[k][1];
	}

	double resultArr[4] = { r1c1, r1c2, r2c1, r2c2 }; // store the dot products in proper order
	static int count = 0;

	for (int k = 0; k < 2; k++) // this loop says that for each row, there are two columns to fill in.
	{
		for (int r = 0; r < 2; r++)
		{
			result[k][r] = resultArr[count]; // resultArr is in proper order, so this fills result correctly
			count++;
		}
	}
}

/*
********************************************************************
**Function: print

**Description: grabs two arrays, treats them like matrices,
multiplies and returns them

**Parameters: the two arrays to be multiplied and an empty array
for their multiplied values to be placed in

**Pre-Conditions: there must be values in each of the rows and columns
of the first and second arrays. The number of values in the r/c
for both must correspond to the parameter requirement.

********************************************************************/

void print(double firstArray[2][3], double secondArray[3][2], double result[2][2])
{
	cout << endl << "The first array has been converted into this 2x3 matrix: ";

	for (int numRows = 0; numRows < 2; numRows++)
	{
		cout << endl;

		for (int numCols = 0; numCols < 3; numCols++)
		{
			cout << setw(6) << firstArray[numRows][numCols];
		}
	}

	cout << endl << "And the second array has been converted into this 3x2 matrix: ";

	for (int numRows = 0; numRows < 3; numRows++)
	{
		cout << endl;

		for (int numCols = 0; numCols < 2; numCols++)
		{
			cout << setw(6) << secondArray[numRows][numCols];
		}
	}

	cout << endl << "The multiplication of those matrices yields the following 2x2 matrix: ";

	for (int numRows = 0; numRows < 2; numRows++)
	{
		cout << endl;

		for (int numCols = 0; numCols < 2; numCols++)
		{
			cout << setw(6) << result[numRows][numCols];
		}
	}

}

int main()
{
	// establish both arrays to be multiplied
	double firstArray[2][3]; 
	double secondArray[3][2];

	createMatrices(firstArray, secondArray); // pass arrays to func where they can be given values by user

	double result[2][2]; // where multiplication of arrays will be stored

	matrixMultiply(firstArray, secondArray, result); // multiply parameters 1 and 2 like matrices, send to result

	print(firstArray, secondArray, result); // print out all three arrays to user

	return 0;
}