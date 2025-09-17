#include <bits/stdc++.h>
using namespace std;


//Single Responsibility Principle (SRP)

// Data structure to store Items
struct Item
{
    int ID;
    string name;
};

// Examples of class that Violates the single Responsiblity principle
/*

As we can see, the Customer class is responsible for multiple tasks:
	- such as maintaining customer details
	- calculating the final bill,
	- generating an invoice.
	
This violates the Single Responsibility Principle, as the class has multiple reasons to change.
*/

class Customer
{
private:
    string name;
    int id;
    vector<Item> items;
    float totalAmount;

public:
    void setName(string name);
    string getName();
    void setId(int id);
    int getId();
    void addItem(Item item);
    void removeItem(Item item);
    float calculateTotalAmount();
    string generateInvoice();
};


//Following the SRP 

/*
Each class has only one responsibility, which makes the code more maintainable and scalable.
If any changes are required in any of these classes, only that class needs to be modified,
rather than the entire class
*/
class CustomerDetails
{
private:
    string name;
    int id;

public:
    void setName(string name);
    string getName();
    void setId(int id);
    int getId();
};

class BillingCalculator
{
private:
    vector<Item> items;

public:
    void addItem(Item item);
    void removeItem(Item item);
    float calculateTotalAmount();
};

class InvoiceGenerator
{
public:
    string generateInvoice(CustomerDetails customerDetails,
                           BillingCalculator billingCalculator);
};

int main()
{
    return 0;
}