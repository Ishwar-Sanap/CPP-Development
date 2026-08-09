#include <iostream>
#include <string>
#include <map>
#include <cmath>

using namespace std;

/*

Design ShoppingCart Class
Solved
Problem: Build a ShoppingCart class that manages items, supports a one-time discount code, and prevents modifications after checkout.

Requirements:

Private map/dictionary of items (item name to price)
Private discount code (can only be applied once)
Private isCheckedOut flag
addItem(name, price): adds an item, but only if the cart hasn't been checked out
applyDiscount(code): if the code is "SAVE10" and no discount has been applied yet, marks the discount as applied and stores it. Returns success/failure.
getTotal(): returns the sum of all prices, minus 10% if a discount was applied
checkout(): marks the cart as checked out if it has at least one item. After checkout, no items can be added and no discounts can be applied.
*/


/**
 
	Encapsulation is one of the four foundational principles of object-oriented design. It is the practice of grouping data 
    (variables) and behavior (methods) that operate on that data into a single unit (typically a class) and restricting direct access 
    to the internal details of that class.

	In simple terms:
		Encapsulation = Data hiding + Controlled access

 */
class ShoppingCart
{
private:
    map<string, double> items;
    bool discountApplied = false;
    bool isCheckedOut = false;

public:
    void addItem(const string &name, double price)
    {
        // Add item to cart, but reject if already checked out
        //Controlled accesss of private data members
        if (!isCheckedOut)
        {
            items[name] = price;
        }
        else
        {
            cout << "Cannot modify a checked-out cart" << endl;
        }
    }

    bool applyDiscount(const string &code)
    {   
        if (code == "SAVE10" && !isCheckedOut && !discountApplied)
        {
            discountApplied = true;
            return true;
        }

        return false;
    }

    double getTotal() const
    {
        // Sum all item prices. If discount was applied, subtract 10%.

        double sum = 0.0;
        for (auto &it : items)
        {
            sum += it.second;
        }
        double discountPerc = 10;

        double discountPrice = sum - ((sum * discountPerc) / 100.0);
        return discountApplied ? round(discountPrice * 100) / 100 : sum;
    }

    void checkout()
    {
        // Mark cart as checked out (only if it has items and isn't already checked out)
        if (!items.empty() && !isCheckedOut)
        {
            isCheckedOut = true;
        }
    }
};

int main()
{
    ShoppingCart cart;
    cart.addItem("Laptop", 999.99);
    cart.addItem("Mouse", 29.99);

    cout << "Total: $" << cart.getTotal() << endl; // 1029.98

    cout << "Discount: " << boolalpha << cart.applyDiscount("SAVE10") << endl; // true
    cout << "Total: $" << cart.getTotal() << endl;                             // 926.98

    cout << "Discount: " << cart.applyDiscount("SAVE10") << endl; // false

    cart.checkout();
    cart.addItem("Keyboard", 79.99);               // Should be rejected
    cout << "Total: $" << cart.getTotal() << endl; // 926.98

    return 0;
}