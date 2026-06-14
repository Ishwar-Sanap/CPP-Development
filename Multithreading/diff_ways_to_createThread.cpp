/*

// 0. In evey application there is a default thread which is main(), in side this we create other threads.
// 1. A thread is also known as lightweight process. Idea is achieve parallelism by dividing a process into multiple threads.
For example:
(a) The browser has multiple tabs that can be different threads.
(b) MS Word must be using multiple threads, one thread to format the text, another thread to process inputs (spell checker)
(c) Visual Studio code editor would be using threading for auto completing the code. (Intellicence)

// WAYS TO CREATE THREADS IN C++11
// 1. Function Pointers (i.e by passing function address)
// 2. Lambda Functions
// 3. Functors
// 4. Member Functions
// 5. Static Member functions



*/

#include <iostream>
#include <thread>
using namespace std;

class Base
{
public:
    void operator()()
    {
        cout << "Inside function object" << endl;
    }

    void fun1()
    {
        cout << "Inside member function" << endl;
    }

    static void fun2()
    {
        cout << "Static member function" << endl;
    }
};

void fun1( int x)
{
    cout << "fun1 is called" << endl;
}

// This will be called by main thread
int main()
{
    // thread constructor accepts something callable as a first argument

    // 1) Function pointer
    thread t1(fun1, 10);  // after the callable function we can pass the arguments that function is excepting.
    t1.join();

    // 2) Lambda functions
    thread t2([]()
              { cout << "Inside lambda function" << endl; });

    t2.join();

    // 3) Functor
    //  Why the extra parentheses matter:
    // thread t3(Base()); → may look like “declare a function named t3” so it won't works as expected
    // thread t3((Base())); → clearly means “create a thread, passing a temporary Base object”
    thread t3((Base()));
    t3.join();

    // 4) Member function
    Base bobj;
    thread t4(&Base::fun1, &bobj); // passng address of member function and address of object, since member function get it in this pointer..
    t4.join();

    //5) Static member function
    thread t5(&Base::fun2);  // static member function does't need object and no this pointer is applicable
    t5.join();

    return 0;
}