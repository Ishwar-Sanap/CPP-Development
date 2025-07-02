#include <bits/stdc++.h>
using namespace std;

// What is a Lambda Expression?
// A lambda expression is an anonymous function (a function without a name) that you can define directly in your code,
// typically passed as arguments to STL algorithms or used for small computations.

/*

[capture](parameters) -> return_type {
    // function body
}

[capture]: Specifies which variables from the outer scope the lambda can access.
Captures:
[ ] → no capture

[=] → capture all by value

[&] → capture all by reference

[x] → capture x by value

[&x] → capture x by reference

(parameters): Just like a normal function parameter list.

-> return_type (optional): Specifies the return type (can usually be omitted).

{ ... }: Function body.
*/

int main()
{
    // Example 1
    // Here, sum is a lambda expression, and auto is used to deduce its type.
    // Note: each lambda has a unique, unnamed compiler-generated class type with an overloaded operator().
    // So, sum is an instance of that unnamed class.
    auto sum = [](int a, int b) -> int // return type -> int is optional
    {
        return a + b;
    };

    int res = sum(4, 6); // calling the function
    // internally since sum is object of compiler-generated class function calls like:
    // sum.operator()(4,6) // calling the overoaded operator() from compiler-generated class for lambdas...

    cout << res << endl;

    // Example 2
    auto sayHello = []()
    { cout << "Hello\n"; };
    sayHello();

    // Example 3
    int x = 1, y = 2;

    auto byValue = [x, y](int k)
    {
        // Not allowed to modify the captured value since they captures by value
        //   x= 2; y++;

        return x + y + k;
    };

    res = byValue(1);
    cout << res << endl;

    auto byValueModified = [x, y]() mutable
    {
        x++;
        y++;

        // mutableAllows modification of captured-by-value variables
    };

    // Example 4
    auto byRef = [&x, &y]()
    {
        x++;
        y++;
    };

    byRef();

    cout << x << " " << y << endl; // 2 3

    // Example 5: Lambda as Comparator

    vector<int> arr = {2, 1, 4, 7};
    sort(arr.begin(), arr.end(), [](auto ele1, auto ele2)
         {
             return ele1 > ele2; // sort descending order
         });

    for (auto ele : arr)
        cout << ele << " ";

    return 0;
}