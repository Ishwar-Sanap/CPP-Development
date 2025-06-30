#include <bits/stdc++.h>
using namespace std;

// A functor is any class object that overloads operator(), so you can use it like a function.

class Multiply
{
public:
    int operator()(int a, int b) const{
        return a * b;
    }
};
int main()
{

    Multiply mult;

    // mult is functor --> it is an object of class Multiply but due to overloded operator() it works like function
    int res = mult(2, 3); // converts to mult.operator()(2,3)

    cout << res << endl; // 6

    // This is functionally equivalent to lambdas
    auto mul = [](int a, int b) { return a * b; };

    res = mul(2,3); // 6

    cout<<res<<endl;

    return 0;
}