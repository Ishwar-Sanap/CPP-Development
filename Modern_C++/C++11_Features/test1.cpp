#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/****** auto type deduction ******** */
int x = 10;
auto str = "hello";   // default type : const char*str = "hello" ,  std::string str = "hello"s
const auto &y = x;    // int &y
const auto *ptr = &x; // const int* ptr

void fun()
{
    vector<int> vt = {4, 5, 6};
    std::sort(vt.begin(), vt.end(), [](auto a, auto b)
              { return a > b; }); // sort descending

    for (auto &e : vt)
    {
        cout << e << " ";
    }
    cout << endl;
}

/****** lambda expression  ******** */
// Inline anonymous functions that can capture variables from their enclosing scope
auto add = [](int a, int b)
{ return a + b; };

// Smart Pointers

/****** constexpr  ******** */
// Computes values at compile time. Functions marked constexpr can run during compilation, moving work out of runtime.

int main()
{
    cout << "Addition : " << add(4, 5) << endl;
    fun();
    return 0;
}