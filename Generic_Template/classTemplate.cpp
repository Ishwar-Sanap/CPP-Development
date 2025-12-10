#include <bits/stdc++.h>
using namespace std;

struct Person
{
    int id;
    string name;

    Person(int i, string str) : id(i), name(str) {}

    friend ostream &operator<<(ostream &os, const Person &obj)
    {
        os << obj.id << " " << obj.name << endl;
        return os;
    }
};

template <class T1, class T2>
class Pair
{
private:
    T1 m_first;
    T2 m_second;

public:
    Pair(T1 a, T2 b) : m_first(a), m_second(b)
    {
    }

    void printValues()
    {
        cout << "first : " << m_first << " " << "second : " << m_second << endl;
    }
};

// Using default type for typename
template <typename T1, typename T2 = int>  
class Data
{
public:
    void show()
    {
        cout << "Default value for second argument type is int" << endl;
    }
};

// Compile time computation
template <int T>
class Squre
{
public:
    static const int value = T * T;
};

int main()
{

    Pair<int, string> p1(1, "abc");
    p1.printValues();

    Person pObj(11, "Amit");

    Pair<int, Person> p2(2, pObj);
    p2.printValues();

    // vector v {1,2,3}; // this syntax is allowed from c++17 compiler will automatically dedcue the class type, no need to vector<int> v = {1,2,3}

    const int val = 10;
    cout << Squre<val>::value << endl; // this computation is haapens at compile time only
    return 0;
}