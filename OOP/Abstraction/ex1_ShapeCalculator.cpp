#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

/*
Design Shape Calculator Class
Solved
Problem: Build a shape calculation system using an abstract class. The abstract Shape class has abstract methods for calculating area and perimeter, plus a concrete describe() method that all shapes inherit.

Requirements:

Abstract Shape class with: abstract area() and perimeter() methods, plus a concrete describe() method that prints "Shape: [name], Area: [area], Perimeter: [perimeter]"
Circle: takes a radius. Area = pi r^2, Perimeter = 2 pi * r
Rectangle: takes width and height. Area = w h, Perimeter = 2 (w + h)
describe() should work for any shape without modification
*/

/*
Abstraction : It is a process of hiding the implementation details and showing only the functionality to the user. 
In C++, abstraction can be achieved using abstract classes and interfaces

Abstract class is a class that cannot be instantiated and is designed to be inherited by other classes. 
It can contain pure virtual functions (methods without implementation) that must be overridden in derived classes. 

In this example, the Shape class is an abstract class with pure virtual functions area() and perimeter(), which are implemented in the derived classes Circle and Rectangle. 
The describe() method is a concrete method that provides a common interface for all shapes to describe themselves, utilizing polymorphism to call the appropriate area() and 
perimeter() methods based on the actual object type.

Abstract class: 
-   The class which contains at least one pure virtual function is called an abstract class.
-   It can contains both pure virtual functions and concrete functions, data members, and constructors.

Interface : 
-   An interface is a class that contains only pure virtual functions and no data members or constructors.
-   It is used to define a contract that derived classes must adhere to, ensuring that they implement specific methods.


*/

class Shape
{
protected:
    string name;

public:
    Shape(const string &name) : name(name) {}
    virtual ~Shape() {}

    virtual double area() = 0;
    virtual double perimeter() = 0;

    void describe()
    {
        // Here we have called virtual functions area() and perimeter(), but those functions will be resolved at runtime based on the actual object type (Circle or Rectangle) due to polymorphism. so the output will be based on the actual object type (Circle or Rectangle) and not the base class (Shape).
        cout << "Shape: " << name << ", Area: " << area() << ", Perimeter: " << perimeter() << endl;
    }
};

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double radius) : Shape("Circle"), radius(radius) {}

    double area() override
    {
        return M_PI * radius * radius;
    }

    double perimeter() override
    {
        return 2 * M_PI * radius;
    }
};

class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double width, double height)
        : Shape("Rectangle"), width(width), height(height) {}

    double area() override
    {
        return width * height;
    }

    double perimeter() override
    {
        return 2 * (width + height);
    }
};

int main()
{
    Circle circle(5.0);
    circle.describe();

    Rectangle rectangle(4.0, 6.0);
    rectangle.describe();

    return 0;
}