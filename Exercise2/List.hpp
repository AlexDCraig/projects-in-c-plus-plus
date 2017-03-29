#ifndef LIST_HPP
#define LIST_HPP

#include "Item.hpp"
#include <iostream>
#include <string>
using namespace std;

class List
{
private:
	Item* products;
	int tracker;
	int size;
	int duplicateElement;

public:
	List();

	~List();

	List(int size);

	List(List &obj);

	void operator=(List &refList); 

	bool operator==(Item &i1); 

	void addItem(Item &item1);

	void removeItem(Item &item1);
		
	void print();

};

#endif
