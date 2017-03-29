/*
********************************************************************
*
*
Program Filename: Item.cpp
*
*
Author: Alex Hoffer
*
*
** Date: 10/18/2015
** Description: Implements Item class. An item contains a name,
unit, quantity, price per unit, and total price of item. Each of these
member data can be described directly by the user EXCEPT for total price,
which is calculated implicitly.
** Input: Uses two strings, an int, and a double to describe an Item.
** Output: Can return two strings, int, and a double for identity. 
*
********************************************************************/

#include "Item.hpp"
#include <iostream>
#include <string>
using namespace std;

Item::Item()
{
	name = "";
	unit = "";
	quantity = 0;
	unitPrice = 0;
	totalPrice = 0;
}

Item::Item(string name, string unit, int quantity, double unitPrice)
{
	this->name = name;
	this->unit = unit;
	this->quantity = quantity;
	this->unitPrice = unitPrice;

	totalPrice = quantity * unitPrice;
}

/*
********************************************************************
*
Function: operator==(Item &it1)
** Description: overloads == operator. 
** Parameters: requires Items on left and right side of ==
** Post-Conditions: The operator returns true if the Items share
name, unit, and unitPrice member variables.
*
********************************************************************/

bool Item::operator==(Item &it1) // compares two items to see if their names, units, and prices are the same
{
	bool same = false;

	if (name == it1.name && unit == it1.unit
		&& unitPrice == it1.unitPrice)
	{
		same = true;
	}

	return same;

}

/*
********************************************************************
*
Function: operator+=(Item &it1)
** Description: overloads +=. Ex: item1 += item2. Takes the quantity of the
right side and tacks it on to the left side's quantity member variable.
** Parameters: Two Item objects, left and right side of +=.
** Pre-Conditions: The items should be equivalent in all aspects aside from their quantities.
** Post-Conditions: Returns an int corresponding to the new quantity.
*
********************************************************************/

int Item::operator+=(Item &it1) // increases the quantity of the left hand value
{
	if (name == it1.getName() && unit == it1.getUnit()
		&& unitPrice == it1.getUnitPrice())
	{
		quantity += it1.quantity;
		return quantity;
	}

	else
		cout << endl << "Those items do not match. Their quantities cannot be added." << endl;
}

void Item::setName(string name)
{
	this->name = name;
}

void Item::setUnit(string unit)
{
	this->unit = unit;
}

void Item::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Item::setUnitPrice(double unitPrice)
{
	this->unitPrice = unitPrice;
}

string Item::getName()
{
	return name;
}

string Item::getUnit()
{
	return unit;
}

int Item::getQuantity()
{
	return quantity;
}

double Item::getUnitPrice()
{
	return unitPrice;
}

/*
********************************************************************
*
Function: getTotalPrice()
** Description: Calculates the totalPrice member variable.
** Pre-Conditions: It is assumed that the Item has a quantity and unitPrice
beyond that of its default values, otherwise totalPrice will be 0.
** Post-Conditions: Returns the totalPrice member variable. Necessary
because totalPrice may change over the course of a program because
List is allowed to change quantities and whatnot. This ensures that
if you want to access totalPrice, you have to use this function,
and this function calculates the totalPrice from the newest info available.
*
********************************************************************/

double Item::getTotalPrice()
{
	totalPrice = quantity * unitPrice;
	return totalPrice;
}

/*
********************************************************************
*
Function: printReceipt()
** Description: Get a look at the Item's member variables.
** Pre-Conditions: getTotalPrice() means totalPrice is the only MV
calculated on the fly and then printed.
*
********************************************************************/

void Item::printReceipt()
{
	cout << quantity << " " << unit << " of " << name << " at $" << unitPrice << " each: ";
	cout << "$" << getTotalPrice() << "." << endl;
}

