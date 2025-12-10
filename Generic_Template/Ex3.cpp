#include <bits/stdc++.h>
using namespace std;

// Template parameter is itselt a template
/*
template template parameter means a template itself is passed as a parameter to another template.
This is useful when you want to write generic code that works with different container templates such as vector, list, deque, etc.
*/

// Noramal template
template <typename T>
class Box
{
};

template <typename T>
class DefaultPolicy
{
public:
    void execute() { std::cout << "Default Policy\n"; }
};

template <typename T>
class FastPolicy
{
public:
    void execute() { std::cout << "Fast Policy\n"; }
};

// Template itselft is template
template <template <typename> class Policy, typename T>
class Algorithm
{
public:
    void run()
    {
        Policy<T> p;
        p.execute();
    }
};

/*
Note:
Number of template parameters must match exactly
If a template requires two parameters, you cannot pass a template requiring one parameter.
*/

// To accept any template with any number of parameters:
// Now you can pass vector, list, even custom templates with multiple type parameters.
// this is useful when we want to use STL continer and it has multiple typename
//It's called --> veriadic templates
template <template <typename...> class Container>
class Wrapper
{
public:
    Container<int> data;
};

int main()
{
    Algorithm<DefaultPolicy, int> a1;
    Algorithm<FastPolicy, int> a2;

    a1.run();
    a2.run();

    Wrapper<std::vector> w1;
    Wrapper<std::list> w2;

    w1.data.push_back(11);
    w1.data.push_back(21);
    w1.data.push_back(51);

    for (auto &it : w1.data)
    {
        cout << it << " ";
    }
    cout << endl;

    w2.data.push_front(1);
    w2.data.push_front(2);
    w2.data.push_front(3);

     for (auto &it : w2.data)
    {
        cout << it << " ";
    }
    cout << endl;
}
