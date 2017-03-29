/* ANSWERS:
 3) It should be easy. The file is read directly into the other file, it just adds a constant to each value. With this in mind, you could theoretically subtract that constant value from each singular character to get the answer.
4) It would be less easy, because the values are out of order. It could still be done, and subtracting the constant value from each value would make it possible, but I would prefer to decrypt the SimpleEncryption version.
*/


// This program demonstrates an application 
// of pure virtual functions.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Encryption
{
 protected:
   ifstream inFile;
   ofstream outFile;
   int fileSize;
 public:
   Encryption(char *inFileName, char *outFileName);
   ~Encryption();
   // Pure virtual function
   virtual char transform(char ch)= 0;
   // Do the actual work.
   virtual void encrypt();
};

//**************************************************
// Constructor opens the input and output file.    *
//**************************************************
Encryption::Encryption(char *inFileName, char *outFileName)
{
   fileSize = 0;
   inFile.open(inFileName);
   outFile.open(outFileName);
   if (!inFile) 
     {
       cout <<  "The file " << inFileName 
            << " cannot be opened.";
       exit(1);
     }
   if (!outFile)
    {
      cout << "The file " << outFileName
           << " cannot be opened.";
      exit(1);
    }
}

//**************************************************
//Destructor closes files.                         *
//**************************************************
Encryption::~Encryption()
{
   inFile.close();
   outFile.close(); 
}

//*****************************************************
//Encrypt function uses the virtual transform         *
//member function to transform individual characters. *
//***************************************************** 
void Encryption::encrypt()
{
  char ch;
  char transCh;
  inFile.get(ch);
  fileSize++;
  while (!inFile.fail())
    {
      transCh = transform(ch);
      outFile.put(transCh);
      inFile.get(ch);
      fileSize++;
    }
}

// The subclass simply overides the virtual
// transformation function
class SimpleEncryption : public Encryption // adds one to character from file
{
protected:
	int key;
public:
   virtual char transform(char ch)
   {
     return ch + key;
   }
   SimpleEncryption(char *inFileName, char *outFileName, int k)
   : Encryption(inFileName, outFileName)
   {
	key = k;
   }
	
   int getFileSize()
   {
	return fileSize;
   }

};

class TransformEncryption : public Encryption // inherits everything
{
protected:
	char *arr;
	int nextSpot;
	int userdef;
	int size;
public:
	TransformEncryption(char *inFileName, char *outFileName, int userdef, SimpleEncryption& item) : Encryption (inFileName, outFileName)
	{	
		size = item.getFileSize();
		arr = new char[size];
		nextSpot = 0;
		srand( time(0));
		this->userdef = userdef;
	}

	virtual char transform(char ch)
	{	
		return ch + userdef; 
	}			

	void arrayCreator(char ch)
	{
		arr[nextSpot] = ch;
		nextSpot++;  
	}

	void encrypt()
	{	
  		char ch;
  		char transCh;
  		inFile.get(ch);
  			while (!inFile.fail())
  			{	
				arrayCreator(transform(ch));
				//arr[nextSpot] = transform(arr[nextSpot]);
      			  	inFile.get(ch);
			}
		
		nextSpot = 0;
		char *array = new char[size];
		int secondArraySize = 0;

		while (secondArraySize < size - 1)
		{
			int origSpot = rand() % size - 1;
			
			bool truth = false;

			for (int k = 0; k < size - 1; k++)
			{
				if (array[k] == arr[origSpot])
				truth = true;
			}

			if (truth == false)
			{
				array[nextSpot] = arr[origSpot];
				nextSpot++;
				secondArraySize++;
			}
		}

		for (int k = 0; k < size - 1; k++)
		{
			outFile.put(array[k]);
		}

}




};


int main()
{
  char inFileName[80], outFileName[80];
  cout << "Enter name of file to encrypt: ";
  cin >> inFileName;
  cout << "What number would you like to add to the char instead of 1? ";
  int newChar;
  cin >> newChar;
  cout << "Enter name of file to receive " 
       << "the encrypted text: ";
  cin >> outFileName;
  SimpleEncryption obfuscate(inFileName, outFileName, newChar);
  obfuscate.encrypt();
   cout << "Please enter the name you'd like to put the transformed text to." << endl;
  char newoutFile[80];
   cin >> newoutFile;
   TransformEncryption obf(inFileName, newoutFile, newChar, obfuscate);
   obf.encrypt();
  return 0;
}
