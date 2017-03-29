/*
********************************************************************
*
*
Program Filename: List.hpp
*
*
Author: Alex Hoffer
*
*
** Date: 10/18/2015
** Description: Draw out skeleton for List class. Can add or remove items,
print, and perform several overloaded operator functions.
*
********************************************************************/

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
