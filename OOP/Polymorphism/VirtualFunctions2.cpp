#include <bits/stdc++.h>
using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base constructor \n";
        // if we call virtual functions from base constructor then  base function will be called
        // since Derived classes construcotr is not yet been called so, vptr is curretnly pointing to base object
        fun(); // base fun
    }
    virtual void fun()
    {
        cout << "Base fun" << endl;
    }

    virtual ~Base()
    {
        cout << "Base destructor" << endl;
    }
};

class Deriverd1 : public Base
{
public:
    Deriverd1() { cout << "Deriverd1 constructor \n"; }
    void fun() override
    {
        cout << "Derived1 fun" << endl;
    }

    void virtual gun()
    {
        cout << "Deriverd1 gun " << endl;
    }

    ~Deriverd1()
    {
        cout << "Derived1 destructor" << endl;
    }
};
class Deriverd2 : public Deriverd1
{
public:
    Deriverd2() { cout << "Deriverd2 constructor \n"; }
    void fun() override
    {
        cout << "Derived2 fun" << endl;
    }

    void virtual gun() override
    {
        cout << "Deriverd2 gun " << endl;
    }

    ~Deriverd2()
    {
        cout << "Derived2 destructor" << endl;
    }
};

int main()
{
    Base *ptrBase = new Deriverd2();
    ptrBase->fun();
    // ptrBase->gun(); // not found in base class
    delete ptrBase;

    cout<<"----------------------------------------\n";
    Deriverd1* ptrD1 = new Deriverd2();
    ptrD1->gun(); // Deriverd2 gun
    
    delete ptrD1;

    return 0;
}