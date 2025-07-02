#include <bits/stdc++.h>
using namespace std;

int main()
{
    int x = 10;   // x --> l value  // 10 --> r value
    int *pX = &x; // we can take address of l value

    int y = (x + 20); // y --> LValue   (x+20) --> rValue

    // int *pRvla = &(x+20); //Error cant' take address of rValue

    // L value Referecens (T&)
    int a = 10;
    int &refA = a; // taking reference of a in refA, so whatever changes we do in any of variable a or refA applyied to both

    cout << a << " " << refA << endl; // 10 10
    refA = 20;
    cout << a << " " << refA << endl; // 20 20

    // int &refB = 10; //Error: initial value of reference to non-const must be an lvalue
    const int &refB = 10;

    // R value References (T&&)
    int &&refR = 10; 

    int z = 11;
    
    //int &&refR = z; // Error : an rvalue reference cannot be bound to an lvalue
    
  // To bind rValue Reference to a lValue  you should use std::move()
    int&& ref = move(z);  // Convert a value to an rvalue.
    return 0;
}