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

int Item::operator+=(Item &it1) // increases the quantity of the left hand value
{
	quantity += it1.quantity;
	return quantity;
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

double Item::getTotalPrice()
{
	totalPrice = quantity * unitPrice;
	return totalPrice;
}

void Item::printReceipt()
{
	cout << quantity << " " << unit << " of " << name << " at $" << unitPrice << " each: ";
	cout << "$" << getTotalPrice() << "." << endl;
}

