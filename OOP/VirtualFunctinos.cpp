#include <bits/stdc++.h>
using namespace std;

// Base class private virtual function is overridden in derived class, but it is not accessible in main function because it is private in base class. 
// but we can call that function through public member function of base class. and it will call the overridden function in derived class because of virtual function and dynamic dispatch.
class Base
{

private:
    virtual void fun()
    {
        cout << "Base fun" << endl;
    }

public:
    //wrapper function to call private virtual function
    void callingFun()
    {
        fun();
    }

    // virtual destructor is required to call derived class destructor when we delete base class pointer pointing to derived class object. otherwise only base class destructor will be called and derived class destructor will not be called, 
    // which can lead to resource leak if derived class has allocated resources in constructor and deallocated in destructor.
    virtual ~Base()
    {
        cout << "Base destructor" << endl;
    }
};

class Deriverd : public Base
{
public:
    void fun() override
    {
        cout << "Derived fun" << endl;
    }

    ~Deriverd()
    {
        cout << "Derived destructor" << endl;
    }
};

int main()
{
    Base *ptrBase = new Deriverd;
    ptrBase->callingFun();

    delete ptrBase;
    
    return 0;
}