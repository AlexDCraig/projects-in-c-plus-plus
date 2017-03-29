#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <sstream>


using namespace std;

bool validates (string &a)
{
	int b = 0;
	int size = a.size();

	string string1("Not valid.");

	for (int k = 0; k < size; k++)
	{
		if (isdigit(a.at(k)) == false)
			throw string1;

		if (a.at(k) < 0)
			throw string1;
	}

		return true;
}

bool valid (string &a, vector <string> vec)
{
	int b = 0;
	int size = a.size();

	for (int k = 0; k < size; k++)
	{
		if (isdigit(a.at(k)) == false)
			throw vec;
	}

	return true;
}

void power (string &a1, string &b1)
{
	validates(a1);
	validates(b1);
	
	stringstream s1(a1);
  	int num1;
  	s1 >> num1;

	stringstream s2(b1);
	int num2;
	s2 >> num2;

	cout << "The exponential expression evaluates to: " << pow(num1, num2) << endl;

}

void averaging()
{
	vector <string> vec;
	string input;
	bool validity = true;

	cout << "Please enter series of numbers: " << endl;

	while (validity == true)
	{
		cin >> input;
		validity = valid(input, vec);
		vec.push_back(input);
	}
}

int main()
{

	string input;
	string input2;
	cout << "Please input two non-negative integers:  " << endl;
	cin >> input;
	cin >> input2;

	try
	{
		power (input, input2);
	}
	catch(string errorString)
	{
		cout << errorString << endl;
		exit (1);
	}
	try
	{
		averaging();
	}
	catch (vector <string> vec)
	{
		cout << "Input is not valid." << endl;
		
		if (vec.size() != 0)
		{
		int size = vec.size();
		int sum = 0;
		double arr[size];

		for (int k = 0; k < size; k++)
		{
			int num;
			string s = vec.at(k);
			stringstream st(s);
			st >> num;

			arr[k] = num;
		}

		for (int i = 0; i < size; i++)
		{
			sum  = sum + arr[i];

		}	
		
		double average = sum/size;
		cout << "The average of all valid inputs is: " << average << endl;

		double secSum = 0;

		for (int i = 0; i < vec.size(); i++)
		{
			secSum += pow((arr[i] - average), 2);
		}

		secSum = secSum/size;

		secSum = pow(secSum, 0.5);

		cout << "The standard deviation of all valid inputs is: " << secSum << endl;
		}

		else
		{
			cout << "No valid inputs." << endl;
		}
	} 

return 0;
}
