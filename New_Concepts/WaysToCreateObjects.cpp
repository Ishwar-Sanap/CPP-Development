#include <iostream>
using namespace std;

class Test
{
private:
    int a{0};
    int b{0};

public:
    void fun()
    {
        cout << "Fun " << a << " " << b << endl;
    }

    Test()
    {
    }
    Test(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
};

// This is the function declaration syntax..
//  Test obj();

// Test obj(){

//     cout<<"Calling obj function"<<endl;
// }

int main()
{
    /*
        This is not object creation this function declaration syntax
        Test obj(); is parsed as a function declaration because the syntax matches a function named obj returning Test and taking no parameters.
        This is the “most vexing parse” in C++.
    */

    // Test obj();
    // obj.fun();

    /*
        Test obj1(5, 6); Is object creation not function declaration because:

        5 and 6 are values, not types.
        A function declaration would require parameter types, for example: Test obj1(int, int);
        So the compiler cannot interpret Test obj1(5, 6); as a function declaration.
    */

    // calls the parameterized constructor
    Test obj1(5, 6);
    obj1.fun();

    // Object creation, it will call default constructor
    Test obj2;
    obj2.fun();

    // object creation using initilizer list, call default constructor
    //T obj3{}; value-initializes and zero-initializes members
    Test obj3{};
    obj3.fun();

    // object creation using initializer list, call parameterized constructor
    Test obj4{7, 8};
    obj4.fun();

    //dynamic object creation
    Test *ptr = new Test();
    ptr->fun();
    delete ptr;


    return 0;
}

