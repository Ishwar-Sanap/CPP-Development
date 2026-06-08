#include <iostream>
using namespace std;

class Shape
{
public:
    int x;
    virtual void draw() = 0;
};

class Circle : public Shape
{
public:
    void draw()
    {
        cout << "Drawing circle" << endl;
    }
};
class Squre : public Shape
{
public:
    void draw()
    {
        cout << "Drawing squre" << endl;
    }
};

void drawShape(Shape *shape)
{
    // Safely downcast to Circle* if shape is pointing to Circle object, else nullptr
    Circle *c1 = dynamic_cast<Circle *>(shape);

    // printing name of the class object
    cout << typeid(*shape).name() << endl;

    // static_cast does not check the type of object at runtime, it just trust the programmer that shape is actually pointing to Squre object, but it is not, so it will cause undefined behavior. 

    // if we are sure that shape is pointing to Squre object then we can use static_cast, but in this case it is not, so it will cause undefined behavior.

    // Squre *s1 = static_cast<Squre *>(shape);
    // s1->draw();

    if (c1 != nullptr)
    {
        // if c1 is not
        c1->draw();
        cout << "Value of x : " << c1->x << endl;
    }
    else
    {
        cout << "Shape is not a Circel object" << endl;
    }
}

int main()
{

    Shape *shape1 = new Circle();
    shape1->x = 11;

    Shape *shape2 = new Squre();

    drawShape(shape1);

    delete shape1;
    delete shape2;

    return 0;
}