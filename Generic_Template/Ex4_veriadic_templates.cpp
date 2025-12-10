#include <bits/stdc++.h>
using namespace std;

//To see how compiler automatically creates the requried template run code on : https://cppinsights.io/

// When theer is remaining single type then return it
//Base condition template
template <typename T>
auto sum(T a)
{
    return a;
}

// veriadic templates
template <typename T1, typename... Args>
auto sum(T1 a, Args... rest)
{
    return a + sum(rest...);
}

int main()
{
    cout << "sum is : " <<  sum(1, 2, 3, 4.5, 5.6) << endl;
    return 0;
}