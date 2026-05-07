#include <iostream>
using namespace std;

class Point
{
public:
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y)
    {
    }
    // 1) Addition
    Point operator+(const Point &other)
    {
        return Point(this->x + other.x, this->y + other.y);
    }

    // 2) Substraction
    Point operator-(const Point &other)
    {
        return Point(this->x - other.x, this->y - other.y);
    }

    //<< and >> operator left operand is ostream and istream so to pass that we have to make it friend function, so implit this pointer parameter get rid off..

    // 3) Printing Point object values Insertion operator (<<)
    friend ostream &operator<<(ostream &out, Point &obj)
    {
        out << "x : " << obj.x << " y : " << obj.y;
        return out;
    }

    // 4) Taking Point object values Input Extraction operator (>>)
    friend istream &operator>>(istream &in, Point &obj)
    {
        in >> obj.x >> obj.y;
        return in;
    }

    // 5) comparison operator ==
    bool operator==(Point &otherObj)
    {
        return (this->x == otherObj.x && this->y == otherObj.y);
    }

    // 6) Pre-Increment ++p
    Point &operator++()
    {
        ++(this->x);
        ++(this->y);
        return *this;
    }

    // 7) Post-Increment p++
    Point operator++(int) // dummy int parameter to distiguish
    {
        //save original obect in temp and return temp
        Point temp = *this;

        //update original opbject
        this->x++;
        this->y++;

        return temp;
    }

    // Similarly also Pre and Post decrement can be overridden.
};

int main()
{
    Point p1(4, 6);

    cout << p1 << endl;

    Point p2;
    // cin >> p2;
    // cout << p2 << endl;

    Point p3(2, 5);

    Point p4 = p1 + p3;

    cout << "Addition is : " << p4 << endl;

    if (p1 == p4)
    {
        cout << "Equal\n";
    }
    else
    {
        cout << "Not equal\n";
    }

    Point resultPre = ++p2; 
    cout << "Pre-Increment"<<endl;
    cout << resultPre << endl;
    cout << p2 << endl;

    cout << "Post-incremented " << endl;

    Point resultPost = p2++;
    cout << resultPost << endl;
    cout << p2 << endl;

    return 0;
}