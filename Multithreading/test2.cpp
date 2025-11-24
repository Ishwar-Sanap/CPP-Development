#include <iostream>
#include <thread>
using namespace std;

class Test
{
public:
    void operator()()
    {
        cout << "Overloaded () operator --> i.e functor " << endl;
    }
    void fun()
    {
        cout << "Inside member function fun()" << endl;
    }

    static void fun2()
    {
        cout << "Inside static member function fun2()" << endl;
    }
};

int main()
{

    Test tObj;

    // Non static member function as a starting function for thread..
    thread t1(&Test::fun, &tObj); // we have passed &tobj because not static member function expect this pointer as default parameter..

    // Static function as the starting function
    thread t2(&Test::fun2);

    // Functor as a starting function..
    thread t3(tObj);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}