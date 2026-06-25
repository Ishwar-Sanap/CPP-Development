#include <iostream>
using namespace std;

/*
std::exception is the Base class for all standard exceptions.

Derived classes:

std::exception
    |
    +-- std::runtime_error
    +-- std::logic_error
    +-- std::invalid_argument
    +-- std::out_of_range
    +-- std::overflow_error
    +-- std::underflow_error
    +-- std::bad_alloc

Example:

throw std::out_of_range("Index out of range");
throw std::runtime_error("Failed to compute ss");


When an exception is thrown, the current block terminates immediately, and local resources are released (except dynamically allocated memory using new).
The stack unwinding occurs as the thrown exception propagates through the call stack to look for the matching catch block.
When the corresponding catch block is found, exception is caught and handled. If not caught, the program terminates

Exception Specification
C++ provides exception specifications to specify that the given function may or may not throw an exception. In modern C++, there are two types of exception specifications:

noexcept: Tells that the given function is guaranteed to not throw an exception.
noexcept(false): Tells that the given function may throw an exception. It is default behaviour in case no exception specification is used.

*********** Custom Exception *****

1. throw creates the exception object
When you write:
InvalidUser("User is not valid");

C++ creates an InvalidUser object and stores it in the runtime’s exception storage. This is typically a separate memory area managed by the exception mechanism.

2. The object is copied/moved into exception storage
The thrown object is not used directly from the local stack frame. The runtime performs:

copy-construction, or
move-construction, if available
This means the original temporary is transferred into the exception object that survives after stack unwinding begins.

3. Stack unwinding happens
The current block exits immediately:

local variables are destroyed
destructors run
control searches upward for a matching catch
4. Matching catch is found
Your catch (const std::exception &e) matches because:

InvalidUser derives from std::exception
the thrown object is still an InvalidUser inside the exception system
catching by reference avoids slicing
So e binds to the actual exception object stored by the runtime.

5. Virtual dispatch returns the right message
Because what() is virtual:

std::exception::what() is overridden by InvalidUser::what()
calling e.what() invokes InvalidUser::what()
the message comes from the derived object
*/

// Custom Exception inheriting the base exception
class InvalidUser : public exception
{
    string msg;

public:
    InvalidUser(const string &str) : msg(str) {}
    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

// Re thrown exception
void process()
{
    throw std::runtime_error("Database connection failed");
}

void func()
{
    try
    {
        try
        {
            process();
        }
        catch (const std::exception &e)
        {
            std::cout << "Logging: " << e.what() << '\n';

            throw; // Re-throw same exception
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Main handled: " << e.what() << '\n';
    }
}

int main()
{
    try
    {
        int choice = 5;

        if (choice == 1)
            throw -1; // throwing int
        else if (choice == 2)
            throw invalid_argument("Invalid option"); // throwing object
        else if (choice == 3)
            throw out_of_range("Out of range");
        else if (choice == 4)
            throw runtime_error("Failed to compute ss");
        else if (choice == 5)
            throw InvalidUser("User is not valid"); // throwing object of custom class
        else
            throw "Unknown Error"; // throwing string
    }
    catch (int err)
    {
        cout << "Error : " << err << endl;
    }
    catch (const std::out_of_range &e)
    {
        cout << "Exception Out of range :  " << e.what() << endl;
    }
    catch (const std::exception &e) // base class catches all built in exceptions
    {
        // when you cath by reference it avoid the copy of object, and also don't peform object slicing due to which we get the same message of derived class
        std::cout << "Exception : " << e.what() << endl;
    }
    catch (...) // executed when no matching catch is found
    {
        // this cath block catches all types of exception, so always place at the end
        cout << "Cath anyting" << endl;
    }

    return 0;
}