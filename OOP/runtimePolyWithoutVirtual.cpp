#include <iostream>
#include <functional>
using namespace std;

class Base
{
public:
    void (*fun)(); // function pointer

    void execute()
    {
        fun(); // runtime decision
    }
};

// Modern Way using function wrapper
class Base2
{
public:
    function<void()> fun;

    void execute()
    {
        fun(); // runtime decision
    }
};

void func1()
{
    cout << "Function 1" << endl;
}
void func2()
{
    cout << "Function 2" << endl;
}

int main()
{

    Base bobj;
    bobj.fun = func2;
    bobj.execute();

    Base2 bobj2;
    bobj2.fun = func1;
    bobj2.execute();

    return 0;
}