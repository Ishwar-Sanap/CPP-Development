#include <bits/stdc++.h>
using namespace std;

template <class T1, class T2>
auto addGeneric(T1 a, T2 b)
{
    return a + b;
}

// Template SPECIALIZATION (must match primary function signature)
/*
Template specialization allows you to write a custom implementation of a template
for a specific type while keeping the general version for all other types.

Ex:
this works for all types.
But sometimes you want a different behavior only for a specific type.
Example: const char* cannot be added using +, so we specialize:


Two Types of Specialization
1️⃣ Full Specialization
Provide implementation for a specific type.

2️⃣ Partial Specialization
You specialize some, not all template parameters. (class templates only).

*/

/*********************** Full Specialization **************************** */
template <>
auto addGeneric<const char *, const char *>(const char *a, const char *b)
{
    int l1 = strlen(a);
    int l2 = strlen(b);

    char *merged = new char[l1 + l2 + 1];
    strcpy(merged, a);
    strcat(merged, b);

    return merged;
}

/*********************** Partial Specialization **************************** */

template <typename T1, typename T2>
class Data
{
public:
    void show()
    {
        cout << "General type" << endl;
    }
};

// partial Specializaiton when second parameter type is int
template <typename T>
class Data<T, int>
{
public:
    void show()
    {
        cout << "Second parameter int type" << endl;
    }
};

main()
{
    const char *res = addGeneric("hello ", "world");
    cout << res << endl;

    Data<string, float> dObj1;
    dObj1.show(); // General type

    Data<float, int> dObj2;
    dObj2.show(); // Second parameter int type

    delete res;
    res = nullptr;

    return 0;
}