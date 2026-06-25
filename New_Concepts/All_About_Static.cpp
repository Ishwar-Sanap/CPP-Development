#include <iostream>
using namespace std;

/** IMP NOTE
 If you make static Singleton obj; as a class member
Then obj becomes a non-local static object, not a lazy singleton.

What changes
static Singleton obj; inside the class is only a declaration.
You still need: this :
Singleton Singleton::obj;

outside the class.

That object is constructed before main() begins.

What issues that creates
Singleton is no longer initialized on first use.
It is created even if nobody calls getInstance().
You lose the main benefit of the function-local static pattern: lazy initialization.
It can introduce static initialization order problems if other globals depend on it across translation units.

class Singleton2
{
public:
    static Singleton2 obj; // declaration
};

Singleton2 Singleton2::obj; // defination, actual object construction
 */

class Singleton
{
public:
    static Singleton &getInstance()
    {
        // this obj will be constructed only once, when this getInstance() is callled  (i.e lazy initialization) and this construction is thread safe
        static Singleton obj;
        return obj;
    }

    void sp()
    {
        cout << "sp method from singleton class" << endl;
    }

    // delete copy constructor and copy assignment to avoid copyping of singleton object
    Singleton(const Singleton &other) = delete;
    Singleton &operator=(const Singleton &other) = delete;

private:
    // private constructor
    Singleton()
    {
    }
};

class Test
{
public:
    static int x;          // static variable can't be initialize here
    static Test objStatic; // declartion of static object
    int y = 0;             // Instance variable can be initialized

    Test()
    {
        cout << "Constructor called" << endl;
    }

    void fun()
    {
        cout << "fun called" << endl;
    }

    static void gun()
    {
        cout << "Static Method : " << x << endl;
        // cout<< this->y <<endl; // this keyword is not allowed in static member function so we can't access instance variable
    }
};

int Test::x = 5;

//Memory allocated in BSS (block starting with symbol)
Test Test::objStatic; // actual static global object creation, constructor get's called  before main

Test objGlobal; // global object

int arr[5] = {1, 5, 4, 2, 1};

void freeFunction()
{
    static int cnt = 0; // static local variable initialization happens only once
    cnt++;

    cout << cnt << endl;
}

int main()
{
    cout << "Start of main" << endl;

    Test::objStatic.fun();
    objGlobal.fun();

    freeFunction();
    freeFunction();
    freeFunction();

    Test::gun();
    objGlobal.gun(); // Static method can also be accessed through object

    // since we have deleted copy assignment and copy constructor we have to take return value as reference
    Singleton &obj = Singleton::getInstance();
    obj.sp();

    return 0;
}