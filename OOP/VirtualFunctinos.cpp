#include <bits/stdc++.h>
using namespace std;

class Base
{

private:
    virtual void fun()
    {
        cout << "Base fun" << endl;
    }

public:
    void callingFun()
    {
        fun();
    }
};

class Deriverd : public Base
{
public:
    void fun() override
    {
        cout << "Derived fun" << endl;
    }
};

int main()
{
    Base *ptrBase = new Deriverd;
    ptrBase->callingFun();

    delete ptrBase;
    
    return 0;
}