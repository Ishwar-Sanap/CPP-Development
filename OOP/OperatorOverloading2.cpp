#include <iostream>
#include <cstring>
using namespace std;

/*
Operators That Cannot Be Overloaded:
	• :: (scope resolution)
	• . (member access)
	• .* (pointer-to-member access)
	• ?: (ternary operator)
	• Sizeof
	
Guidelines:
	• Don't change expected behavior (+ should add, not divide)
	• Maintain consistency between related operators
	• Return references for assignment operators

*/

class Vector2D
{
private:
    double x, y;

public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Arithmetic operators
    Vector2D operator+(const Vector2D &other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D &other) const
    {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(double scalar) const
    {
        return Vector2D(x * scalar, y * scalar);
    }

    // Compound assignment
    Vector2D &operator+=(const Vector2D &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Unary operators
    Vector2D operator-() const
    {
        return Vector2D(-x, -y);
    }

    // Comparison operators
    bool operator==(const Vector2D &other) const
    {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Vector2D &other) const
    {
        return !(*this == other);
    }

    // Subscript operator
    double &operator[](int index)
    {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else
            throw out_of_range("Index must be 0 or 1");
    }

    // Stream operators (must be friend)
    friend ostream &operator<<(ostream &os, const Vector2D &v);
    friend istream &operator>>(istream &is, Vector2D &v);
};

ostream &operator<<(ostream &os, const Vector2D &v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

istream &operator>>(istream &is, Vector2D &v)
{
    is >> v.x >> v.y;
    return is;
}

// Example with increment/decrement operators
class Counter
{
private:
    int count;

public:
    Counter(int c = 0) : count(c) {}

    // Pre-increment (++obj)
    Counter &operator++()
    {
        ++count;
        return *this;
    }

    // Post-increment (obj++)
    Counter operator++(int)
    { // int is dummy parameter
        Counter temp = *this;
        count++;
        return temp;
    }

    // Pre-decrement (--obj)
    Counter &operator--()
    {
        --count;
        return *this;
    }

    // Post-decrement (obj--)
    Counter operator--(int)
    {
        Counter temp = *this;
        count--;
        return temp;
    }

    int getCount() const { return count; }

    friend ostream &operator<<(ostream &os, const Counter &c)
    {
        os << c.count;
        return os;
    }
};

// Function call operator - making objects callable
class Multiplier
{
private:
    int factor;

public:
    Multiplier(int f) : factor(f) {}

    // Overload function call operator
    int operator()(int value) const
    {
        return value * factor;
    }

    int operator()(int a, int b) const
    {
        return (a + b) * factor;
    }
};

// Smart pointer example - arrow operator
class SmartPointer
{
private:
    int *ptr;

public:
    SmartPointer(int *p = nullptr) : ptr(p) {}

    ~SmartPointer()
    {
        delete ptr;
    }

    // Dereference operator
    int &operator*()
    {
        return *ptr;
    }

    // Arrow operator
    int *operator->()
    {
        return ptr;
    }
};

// Type conversion operator
class Fraction
{
private:
    int numerator;
    int denominator;

public:
    Fraction(int n, int d = 1) : numerator(n), denominator(d) {}

    // Conversion to double
    operator double() const
    {
        return static_cast<double>(numerator) / denominator;
    }

    // Conversion to bool
    explicit operator bool() const
    {
        return numerator != 0;
    }

    friend ostream &operator<<(ostream &os, const Fraction &f)
    {
        os << f.numerator << "/" << f.denominator;
        return os;
    }
};

int main()
{
    cout << "=== Arithmetic Operators ===" << endl;
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);

    Vector2D v3 = v1 + v2;
    Vector2D v4 = v1 - v2;
    Vector2D v5 = v1 * 2;

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 + v2 = " << v3 << endl;
    cout << "v1 - v2 = " << v4 << endl;
    cout << "v1 * 2 = " << v5 << endl;

    cout << "\n=== Subscript Operator ===" << endl;
    cout << "v1[0] = " << v1[0] << endl;
    cout << "v1[1] = " << v1[1] << endl;
    v1[0] = 10;
    cout << "After v1[0] = 10: " << v1 << endl;

    cout << "\n=== Increment/Decrement ===" << endl;
    Counter c(5);
    cout << "Initial: " << c << endl;
    cout << "Pre-increment: " << ++c << endl;
    cout << "Post-increment: " << c++ << endl;
    cout << "After post-increment: " << c << endl;

    cout << "\n=== Function Call Operator ===" << endl;
    Multiplier times3(3);
    cout << "times3(5) = " << times3(5) << endl;
    cout << "times3(2, 4) = " << times3(2, 4) << endl;

    cout << "\n=== Type Conversion ===" << endl;
    Fraction f(3, 4);
    cout << "Fraction: " << f << endl;
    double d = f; // Implicit conversion
    cout << "As double: " << d << endl;

    if (f)
    { // Explicit conversion to bool
        cout << "Fraction is non-zero" << endl;
    }

    return 0;
}