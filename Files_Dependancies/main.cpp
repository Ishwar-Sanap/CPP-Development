#include <bits/stdc++.h>
using namespace std;

extern double getAreaOfCircle(double);

int main()
{
    double area = getAreaOfCircle(2.3);
    cout << "Area of circle " << area << endl;
    return 0;
}

// Commands to run 
// step1 : g++ main.cpp helper1.cpp -o Myexe
// step2 : ./Myexe