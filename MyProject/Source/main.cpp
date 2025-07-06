#include <iostream>
using namespace std;

extern double getAreaOfCircle(double);
double getAreaOfRectangle(double, double);

int main()
{
    double circleArea = getAreaOfCircle(4.1);
    double reactangleArea = getAreaOfRectangle(10, 6);

    cout << "Area of circle : " << circleArea << endl;
    cout << "Area of rectangle : " << reactangleArea << endl;
    
    return 0;
}