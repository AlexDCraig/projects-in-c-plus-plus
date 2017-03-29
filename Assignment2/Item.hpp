#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
using namespace std;

class Item
{
private:
	string name;
	string unit;
	int quantity;
	double unitPrice;
	double totalPrice;

public:
	
	Item();

	Item(string name, string unit, int quantity, double unitPrice);

	bool operator==(Item &it1); // compares two items to see if their names, units, and prices are the same

	int operator+=(Item &it1); // increases the quantity of the left hand value

	void setName(string name);

	void setUnit(string unit);

	void setQuantity(int quantity);

	void setUnitPrice(double unitPrice);

	string getName();

	string getUnit();

	int getQuantity();

	double getUnitPrice();

	double getTotalPrice();

	void printReceipt();

};

#endif