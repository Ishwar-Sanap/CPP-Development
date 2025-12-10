#include <bits/stdc++.h>
using namespace std;

// What is need of templates in C++ ??
// Template is blueprint of the function and compiler dynamically decide which data type it should used based on passed arguments

int Add(int a, int b)
{
    return a + b;
}

double Add(double a, double b)
{
    return a + b;
}

string Add(string a, string b)
{
    return a + b;
}

/*
In above functions, the logic is same but for different data types we have write seperate overloaded definations
and code becomes messy if we are writing some library function that will be support multiple data types..

Function Templates
Function templates allow a single function definition to work with multiple data types.
The compiler automatically generates the correct version of the function at compile time based on the arguments provided.
*/

// As this function is taking 2 parameter we have declare template that also take 2 parameters
template <class T1, class T2>                  // or template <typename T1, typename T2>
auto addGeneric(T1 a, T2 b) -> decltype(a + b) // trailing return type.
{
    return a + b; // return value can be of any data type..
}

int main()
{
    // simple function
    // cout << "Result is : " << Add(5, 6) << endl;
    // cout << "Result is : " << Add(5.5, 6.0) << endl; // if we pass double value then it should be taken as double
    // cout << "Result is : " << Add("abc", "def") << endl;

    cout << "Result is : " << addGeneric(5, 6) << endl;
    cout << "Result is : " << addGeneric(5.5, 6) << endl;

    string a = "abc", b = "def";
    cout << "Result is : " << addGeneric(a, b) << endl;

    return 0;
}