#include <bits/stdc++.h>
using namespace std;

// 1. Copy constructor approach
// This is the simplest way to copy an object when you already know its concrete type.

/*
class Circle {
private:
    int radius;

public:
    Circle(int r) : radius(r) {}

    Circle(const Circle& other) {
        radius = other.radius;
    }

    void print() const {
        cout << "Circle radius = " << radius << endl;
    }
};

int main() {

This is clean and fine.

Problem
The caller must know the exact class:


Circle c2(c1);
If you later have Rectangle, Triangle, Enemy, Document, etc., then the calling code must know each concrete type and its copy constructor.

That becomes messy when you work through a base class pointer.

    Circle c1(10);
    Circle c2(c1);   // copy constructor

    c1.print();
    c2.print();


    return 0;
}

*/

//2. Prototype Interface
// Prototype pattern lets you clone existing objects
// (deep or shallow copy), instead of constructing new ones.

class Shape
{
public:
    virtual ~Shape() = default;
    virtual Shape *clone() const = 0;
    virtual void print() const = 0;
};

// Concrete classes implement clone()
class Circle : public Shape
{
private:
    int radius;

public:
    Circle(int r) : radius(r) {}

    Circle(const Circle &other)
    {
        radius = other.radius;
    }

    Shape *clone() const override
    {
        return new Circle(radius);
    }

    void print() const override
    {
        cout << "Circle radius = " << radius << endl;
    }
};

class Rectangle : public Shape
{
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    Rectangle(const Rectangle &other)
    {
        width = other.width;
        height = other.height;
    }

    Shape *clone() const override
    {
        return new Rectangle(width, height);
    }

    void print() const override
    {
        cout << "Rectangle " << width << " x " << height << endl;
    }
};

int main()
{
    Shape *s1 = new Circle(10); // new Rectangle(10,20);
    Shape *s2 = s1->clone();

    //Now the caller does not need to know whether s1 is a Circle or a Rectangle. The object copies itself.


    s1->print();
    s2->print();

    delete s1;
    delete s2;

    return 0;
}