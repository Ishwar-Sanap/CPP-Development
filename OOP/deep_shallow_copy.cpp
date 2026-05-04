#include <iostream>
using namespace std;

// Always make sure, when class has raw pointers, dynamically allocated memory then use Rule of 3 and Rule of 5
/*
Rule of 3
    - Define Copy constructor
    - Define Copy assignemnt
    - Define Destrutor

Rule of 5
    - Define Copy constructor
    - Define Copy assignemnt
    - Define move constructor
    - Define move assignemnt
    - Define Destrutor

Rule of 0 :
    use RAII continers like smart poiters, vectors, they automatically manages the resources

*/
struct Student
{
    string name{};
    int age{};

    Student(const string &strName, int iAge)
    {
        name = strName;
        age = iAge;
    }
};

class TestShallow
{
public:
    Student *m_ptObjStudent{nullptr};
    TestShallow(const string &strName, int iAge)
    {
        m_ptObjStudent = new Student(strName, iAge);
    }

    // Copy constructor, shallow copy
    TestShallow(const TestShallow &OtherObj)
    {
        m_ptObjStudent = OtherObj.m_ptObjStudent;
    }

    ~TestShallow()
    {
        if (m_ptObjStudent)
        {
            //if one object deletes the memory then another object still points the same memory that is not exis, becomes dangling pointer
            //double deleting memory due to shallow copy cause segementation fault.
            delete m_ptObjStudent;
            m_ptObjStudent = nullptr;
        }
    }

    // Overloading << operator to print object values
    // << operator expects left side operand must be of type ostream, but class member function has default this pointer as first parameter input.
    // so we used friend function. and this becomes non member function now, but can access private variable also.
    friend ostream &operator<<(ostream &os, const TestShallow &obj);
};
class TestDeep
{
public:
    Student *m_ptObjStudent{nullptr};
    TestDeep(const string &strName, int iAge)
    {
        m_ptObjStudent = new Student(strName, iAge);
    }

    // Copy constructor, Deep copy
    TestDeep(const TestDeep &OtherObj)
    {
        m_ptObjStudent = new Student(OtherObj.m_ptObjStudent->name, OtherObj.m_ptObjStudent->age);
    }

    ~TestDeep()
    {
        if (m_ptObjStudent)
        {
            delete m_ptObjStudent;
            m_ptObjStudent = nullptr;
        }
    }

    // Overloading << operator to print object values
    // << operator expects left side operand must be of type ostream, but class member function has default this pointer as first parameter input.
    // so we used friend function. and this becomes non member function now, but can access private variable also.
    friend ostream &operator<<(ostream &os, const TestDeep &obj);
};

ostream &operator<<(ostream &os, const TestShallow &obj)
{
    os << " Name: " << obj.m_ptObjStudent->name << ", Age: " << obj.m_ptObjStudent->age << endl;
    return os;
}

ostream &operator<<(ostream &os, const TestDeep &obj)
{
    os << " Name: " << obj.m_ptObjStudent->name << ", Age: " << obj.m_ptObjStudent->age << endl;
    return os;
}
int main()
{
    /*************** Shallow Copy ****************** */
    TestShallow obj1("John", 24);

    cout << obj1 << endl;

    TestShallow obj2(obj1);

    cout << obj2 << endl;

    // hallow copy → both obj1 and obj2 now point to the same Student object in heap.

    // What happens next?
    // obj1.m_ptObjStudent → points to Student
    // obj2.m_ptObjStudent → points to same Student

    // Now when destructors run:
    //  First destructor deletes the memory ✔️
    //  Second destructor tries to delete already deleted memory ❌
    //  This causes undefined behavior (crash / double free error)

    /*************** Deep Copy ****************** */
    // Now each object has its own copy → no double delete.
    // TestDeep obj1("John", 26);
    // cout << obj1 << endl;

    // TestDeep ob2 = obj1;
    // cout << ob2 << endl;

    return 0;
}