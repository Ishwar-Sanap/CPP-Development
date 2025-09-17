#include <bits/stdc++.h>
using namespace std;

class Rectangle
{
public:
    virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }
    int getArea() const { return width * height; }

protected:
    int width = 0;
    int height = 0;
};

class Square : public Rectangle
{
public:
    void setWidth(int w) override
    {
        width = height = w; // Changing width affects height!
    }

    void setHeight(int h) override
    {
        width = height = h; // Changing height affects width!
    }
};

void printArea(Rectangle &obj)
{
    obj.setHeight(5);
    obj.setWidth(10);

    // For Rectangle obj Area will be 50
    cout << obj.getArea() << endl;
}

void printArea(Square &obj)
{
    obj.setHeight(5);
    obj.setWidth(10);

    // For squre obje the Area will be 100
    cout << obj.getArea() << endl;
}

// since we passing the child class object to printArea function it beahves differently
// than passing Rectangle obj, so it's violates the LSP principle

// TO fix it use the separate classe or Composition

class Shape
{
    virtual double getArea() = 0;
};

class Reactangle1 : public Shape
{
public:
    int width = 0;
    int height = 0;

    Reactangle1(int w, int h)
    {
        width = w;
        height = h;
    }

    double getArea() { return width * height; }
};

class Squre1 : public Shape
{
public:
    int height = 0;

    Squre1(int h)
    {
        height = h;
    }

    double getArea() { return height * height; }
};

int main()
{
    return 0;
}