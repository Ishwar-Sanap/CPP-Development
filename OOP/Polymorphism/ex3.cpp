#include <iostream>
using namespace std;
#include <iostream>

// Vtable for Base
class Base
{
public:
    Base()
    {
    }
    virtual void show() { std::cout << "Base Show\n"; }
    virtual void print() { std::cout << "Base Print\n"; }
};

// Vtable for Derived
class Derived : public Base
{
public:
    void show() override { std::cout << "Derived Show\n"; } // Overridden
    // print() is inherited as-is

    
};

int main()
{
    cout << "Size of Base class : " << sizeof(Base) << " Bytes" << endl; // 8 Bytes (due to vptr)
    cout << "Size of Derived class : " << sizeof(Derived) << " Bytes" << endl; // 8 Bytes (due to vptr)

    // you have created 2 different objects but as there are only 2 classes exist which contains Virtual functions
    // so there will be only 2 Vtables exists
    Base *ptr = new Derived();
    ptr->show(); // calls Derive Show

    Base *ptr2 = new Derived();
    ptr2->print(); // calls Base Print

    return 0;
}
