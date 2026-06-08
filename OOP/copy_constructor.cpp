#include <iostream>
using namespace std;

class Point
{
public:
    int x;
    int y;
    Point() : x(0), y(0)
    {
        cout << "Default constructor called" << endl;
    }

    Point(int _x, int _y) : x(_x), y(_y)
    {
        cout << "Parameterized constructor called" << endl;
    }

    Point(const Point &ohter)
    {
        cout << "Copy constructor called" << endl;
        x = ohter.x;
        y = ohter.y;
    }

    ~Point()
    {
        cout << "Destructor Called" << endl;
    }
};

/*
When is a Copy Constructor Invoked?
Copy constructors come into play in several scenarios:
1) Object Initialization: When you create a new object from an existing object.
2) Function Call by Value: When you pass an object to a function by value.
3) Return by Value: When a function returns an object by value.

*/

// copy-constructor call for the function parameter
void PrintObjectPassByValue(Point obj)
{
    cout << "Function paramter Point obj Recieved by copy" << endl;
    cout << "x : " << obj.x << " y : " << obj.y << endl;
    cout << "Function paramter Point obj goes out of scop" << endl;
}

void PrintObjectPassByRef(const Point &obj)
{
    cout << "Function paramter Point obj Recieved by ref " << endl;
    cout << "x : " << obj.x << " y : " << obj.y << endl;
    cout << "Function paramter Point obj goes out of scop" << endl;
}

Point GetObjectByValue()
{
    Point testObj(-1, -2);
    return testObj; // local object being copied into the function return object
}

int main()
{

    Point obj1(11, 21);
    Point obj2(obj1);
    // Point obj3(Point(3, 4)); //does not compile, because the temporary Point(1,2) is an rvalue 
    //and it can't bind to lvalue. so we have to add const in copy constructor

    PrintObjectPassByValue(obj1);
    cout << "Executed PrintObjectPassByValue() function" << endl;

    PrintObjectPassByRef(obj1);

    /*
    In C++17 and later: copy elision is mandatory here, so Point testObj = GetObjectByValue(); will not call the copy constructor.
    In older standards (pre-C++17): compilers often still elide the copy, but if elision does not happen, then yes — the copy constructor would be called.
    */
    Point testObj = GetObjectByValue(); // return temporary object being copied into the caller’s testObj
    return 0;
}