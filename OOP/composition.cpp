#include <iostream>
using namespace std;

/*

For a class with composition:
    1. Memory for the whole object is allocated.
    2. Base class constructors run (if any).
    3. Member objects are constructed in the order they are declared.
    4. The containing class's constructor body executes.
    5. Destructor are called in reverse order of constructor

This construction order is guaranteed by the C++ language and cannot be changed.
*/
class Engine
{
public:
    Engine()
    {
        cout << "Engine constructed" << endl;
    }
};

class Tyre
{
public:
    Tyre(int Size)
    {
        cout << "Tyre constructed with size: " << Size << endl;
    }
};

class Car
{
    // Member objects are constructed in the order they are declared.
private:
    // Composition: Car has an Engine
    Engine engine; // Only declaration here, no object is created yet
    Tyre tyre;     // Only declaration here, no object is created yet
public:
    Car() : tyre(16)   // Member initializer list to initialize tyre and engine
    {
        // Before the constructor of Car is executed, the constructor of Engine is called automatically.
        //  The Engine object is created as part of the Car object.
        // Note : Always remember that the order of construction is from base class to derived class, and for member objects, they are constructed in the order they are declared in the class.
        //  All member objects are constructed before the body of the constructor is executed.

        cout << "Car constructed" << endl;
    }
};

int main()
{
    Car myCar; // Creating an object of Car class.

    return 0;
}