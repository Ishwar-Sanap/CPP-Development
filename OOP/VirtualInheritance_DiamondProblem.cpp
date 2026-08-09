#include <bits/stdc++.h>
using namespace std;

class Base
{
public:
    Base() { cout << "Base constructor \n"; }
    ~Base() { cout << "Base destructor" << endl; }
    void fun() { cout << "Base fun" << endl; }
};

class Deriverd1 : virtual public Base
{
public:
    Deriverd1() { cout << "Deriverd1 constructor \n"; }
    ~Deriverd1() { cout << "Derived1 destructor" << endl; }
};
class Deriverd2 : virtual public Base
{
public:
    Deriverd2() { cout << "Deriverd2 constructor \n"; }
    ~Deriverd2() { cout << "Derived2 destructor" << endl; }
};

class Bottom : public Deriverd1, public Deriverd2
{
public:
    Bottom() { cout << "Bottom constructor \n"; }
    ~Bottom() { cout << "Bottom destructor" << endl; }
};
int main()
{

    Bottom bobj;
    bobj.fun();

    return 0;
}

/*
//Without Virtual Inheritance : 2 copies of Base class
Base constructor 
Deriverd1 constructor 
Base constructor 
Deriverd2 constructor 
Bottom constructor 
Bottom destructor
Derived2 destructor
Base destructor
Derived1 destructor
Base destructor
*/

/*
With Virtual Inheritance: only one copy of Base class

Base constructor 
Deriverd1 constructor 
Deriverd2 constructor 
Bottom constructor 
Base fun
Bottom destructor
Derived2 destructor
Derived1 destructor
Base destructor
*/