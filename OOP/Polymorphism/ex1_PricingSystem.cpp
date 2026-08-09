#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;


/*
Requirements:

Abstract Discount class with a label field (protected), an abstract apply(price) method that returns the discounted price, and a concrete describe(originalPrice) method that prints "label: $originalPrice -> $discountedPrice".
PercentageDiscount: takes a percentage (e.g., 20 means 20% off). Label is "20.0% off". Returns price * (1 - percentage/100).
FlatDiscount: takes a fixed amount off. Label is "$15.0 off". Returns price - amount (minimum 0).
BuyOneGetOneFree: halves the price. Label is "Buy 1 Get 1 Free". Returns price / 2.
OrderProcessor class with a processOrder(itemName, price, discount) method that prints the item name and calls describe() on the discount.


Solution explation : 
Object-Oriented Design
    • The class hierarchy is clean and matches the problem well: Discount as an abstract base class, with concrete discount types overriding apply().
    • OrderProcessor depends on the abstract Discount type, which is a good polymorphic design.
Design Patterns
    • This is a solid Strategy pattern implementation: each discount type encapsulates its own pricing algorithm.
    • The shared formatting behavior in Discount::describe() is well placed in the base class.
SOLID Principles
    • SRP: Responsibilities are well separated: discount calculation, formatting, and order processing are distinct.
    • OCP: New discount types can be added without changing OrderProcessor.
    • LSP: All subclasses behave correctly through the base Discount interface.
    • DIP: OrderProcessor works with the abstraction, not concrete discount classes.
Correctness
    • The output matches the expected result exactly.
    • All discount calculations are correct, including the minimum-zero behavior for FlatDiscount.
Code Quality
    • The code is readable and structured clearly.
    • Naming is descriptive and consistent.

Formatting in describe() is implemented cleanly and produces the required output.       

*/
class Discount
{
protected:
    string label;

public:
    Discount(const string &label) : label(label) {}
    virtual ~Discount() {}

    virtual double apply(double price) = 0;

    void describe(double originalPrice)
    {   
        
        //snprintf is used for formatting..
        char basePrice[32];
        snprintf(basePrice, sizeof(basePrice), "%.2f", originalPrice);
        char discountedPrice[32];
        snprintf(discountedPrice, sizeof(discountedPrice), "%.2f", apply(originalPrice));

        cout << label << ": $" << basePrice << " -> " << "$" << discountedPrice << endl;
    }
};

class PercentageDiscount : public Discount
{
    double percentage;

public:
    PercentageDiscount(double percentage)
        : Discount(string())
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "%.1f", percentage);
        this->label = string(buf) + "% off";
        this->percentage = percentage;
    }

    double apply(double price) override
    {
        return price * (1 - percentage / 100);
    }
};

class FlatDiscount : public Discount
{
    double amount;

public:
    FlatDiscount(double amount)
        : Discount(string())
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "%.1f", amount);
        this->label = "$" + string(buf) + " off";
        this->amount = amount;
    }

    double apply(double price) override
    {
        return max(price - amount, 0.0);
    }
};

class BuyOneGetOneFree : public Discount
{
public:
    BuyOneGetOneFree() : Discount("Buy 1 Get 1 Free") {}

    double apply(double price) override
    {
        return price / 2;
    }
};

class OrderProcessor
{
public:
    void processOrder(const string &itemName, double price, Discount &discount)
    {
        cout << "Item: " << itemName << endl;
        discount.describe(price);
    }
};

int main()
{
    OrderProcessor processor;

    PercentageDiscount pct(20);
    FlatDiscount flat(15);
    BuyOneGetOneFree bogo;

    processor.processOrder("Laptop", 999.99, pct);
    processor.processOrder("Headphones", 49.99, flat);
    processor.processOrder("Keyboard", 79.98, bogo);
    return 0;
}